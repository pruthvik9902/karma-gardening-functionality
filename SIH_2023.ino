#include <dht11.h>
#include <DHT.h>
#include <DHT_U.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <dht11.h>
#define RX 2
#define TX 3
#define dht_apin 8 // Analog Pin sensor is connected
dht11 dhtObject;
int valSensor0 = 1;
//int valSensor1 = 1;
const int dry = 1000;
const int wet = 100;
int motor0 = 9;
int motor1 = 10;
int led = 13;
int buz = A1;
SoftwareSerial esp8266(RX,TX);
const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
Serial.begin(115200);
lcd.begin(16, 4);
pinMode(motor0,OUTPUT);
pinMode(motor1,OUTPUT);
Serial.begin(9600);
pinMode(led, OUTPUT);
pinMode(buz,OUTPUT);
}
void loop() {
lcd.setCursor(0, 1);
lcd.print("Moisture0:");
lcd.print(getMoistureValue0());
lcd.setCursor(0, 0);
lcd.print("Temprature:");
lcd.print(getTemperatureValue());
lcd.setCursor(4, 2);
lcd.print("Humidity:");
lcd.print(getHumidityValue());
lcd.setCursor(4, 3);
//lcd.print("Moisture1:");
//lcd.print(getMoistureValue1());
tone(buz,10000,5000);
noTone(A1);
if ( getMoistureValue0() < 50 )
//Serial.print(" Soil Moisture0 % = ");
{
digitalWrite(motor0, HIGH);
delay(100);
digitalWrite(led,HIGH);
delay(100);
digitalWrite(buz,HIGH);
delay(100);
}
else {
digitalWrite(motor0, LOW);
delay(100);
digitalWrite(led,LOW);
delay(100);
}
if ( getMoistureValue1()> 20 )
{
digitalWrite(motor1, HIGH);
delay(100);
digitalWrite(motor1, LOW);
}
else {
digitalWrite(motor1, LOW);
}
}
int getMoistureValue0(){
int sensorVal0 = analogRead(A0);
int percentageHumidity0 = map(sensorVal0, wet, dry, 100, 0);
Serial.print(" Soil Moisture0 % = ");
Serial.print(percentageHumidity0 );
delay(10);
return int(percentageHumidity0);
}
int getMoistureValue1(){
int sensorVal1 = analogRead(A1);
int percentageHumidity1 = map(sensorVal1, wet, dry, 100, 0);
Serial.print(" Soil Moisture1 % = ");
Serial.print(percentageHumidity1 );
delay(10);
return int(percentageHumidity1);
}
String getTemperatureValue(){
dhtObject.read(dht_apin);
Serial.println(" Temperature(C)= ");
int temp = dhtObject.temperature;
Serial.println(temp);
delay(50);
return String(temp);
}
String getHumidityValue(){
dhtObject.read(dht_apin);
Serial.print(" Humidity in %= ");
int humidity = dhtObject.humidity;
Serial.println(humidity);
delay(10);
return String(humidity);
}
