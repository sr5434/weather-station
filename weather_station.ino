#include <Adafruit_BMP085.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTTYPE DHT11
Adafruit_BMP085 bmp;
LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(13, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.clear();
  lcd.backlight();
  if (!bmp.begin()) {
      Serial.println("Could not find a valid BMP085 sensor, check wiring!");
      while (1); // Stop execution if sensor is not found
  }
  pinMode(2, INPUT);
}
  
void loop() {
    float temperature = bmp.readTemperature();
    float humidity = dht.readHumidity();
    float pressure = bmp.readPressure();
    int metric = digitalRead(2);
    lcd.setCursor(0,0);
    lcd.print("Tmp:");
    lcd.setCursor(0,1);
    if (metric == 1){
      lcd.print(String(round(temperature))+"C");
    } else {
      //User wanted imperial units
      lcd.print(String(round((temperature*1.8)+32))+"F");
    }
    
    lcd.setCursor(5, 0);
    lcd.print("Hmd:");
    lcd.setCursor(5, 1);
    lcd.print(String(round(humidity))+"%");

    lcd.setCursor(10,0);
    lcd.print("Prs:");
    lcd.setCursor(10,1);
    lcd.print(String(round(pressure/1000))+"KPa");
    delay(500);
}