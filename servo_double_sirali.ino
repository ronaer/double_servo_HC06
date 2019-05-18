/*TR.ALP.18 www.ronaer.com
  Örnek android uygulaması:
  https://play.google.com/store/apps/details?id=appinventor.ai_ysrggs.Servomotorkontrol
*/
#include <SoftwareSerial.h> // Yazılımsal TX RX bluetooth kütüphanesi eklendi
#include <Servo.h>          // servo kütüphanesi eklendi 
Servo myservo, myservo1;    // 1. ve 2.servo motor isimleri (nesneleri) tanımlandı

//burayı yanlış bağlamayın, bluetooth modülünü yakmayın!
int bluetoothTx = 10;       // bluetooth tx'i 10. pine atayalım
int bluetoothRx = 11;       // bluetooth rx'i 11. pine atayalım

// GND-->2kohm--bluetootRX---1kohm-->arduino pin(11) ile gerilim bölücü yapmanız önerilir,
// yapmasanız da çalışıyor ancak 5V-->3.3V nedeni ile bir süre sonra bluetooth komut almıyor!

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx); //Kütüphane komutu ile Bluetooth Tx 10, Bluetooth Rx 11. pin oldu

void setup()
{
  myservo.attach(9);      // 1.Servo sinyal kontrol pini 9.pin oldu
  myservo1.attach(6);     // 2.Servo sinyal kontrol pini 6. pin oldu
  //Servolarla ilişkilendirdiğiniz pinler ~PWM pini olmalı! (Uno PWM pinleri: 3, 5, 6, 9, 10, ve 11 dir)
 
  Serial.begin(9600);    //Bilgisayar ile seri iletişim başlatalım ve 9600 B olsun

  bluetooth.begin(9600);  // Androide bağlı Bluetooth modülü ile seri iletişim başlatalım ve 9600 B olsun(varsayılan)
  myservo.write(0);       //servolarımız program ilk çalıştığında 0 pozisyonuna gelsin.
  myservo1.write(0);
}

void loop()
{
  //Bluetooth verisini okutalım ve eğer veri gelirse diye başlayalım:

  if (bluetooth.available() > 0 )     // Android uygulamasından bluetooth verisi geldiğinde;
  {
    int servopos = bluetooth.read();  // Bu veriyi servopos (servoposition) adlı integer değişkenine aktaralım
    Serial.println(servopos);         // bluetooth dan gelen anlık servopos verisini serial port dan görelim
    if (servopos == 90) {             // Eğer BT dan 90 verisi geldiğinde;
      myservo.write(servopos);        // 1.servo motora aktaralım
      delay(1000);                    // 1 saniye bekleyelim,  
      myservo1.write(servopos);       // ve 2.servo motora aktaralım
      delay(5);                       // azıcık mola versinler...
    }
    else if (servopos == 0) {         // Eğer BT dan 0 verisi gelirse
      myservo1.write(servopos);       //2.servo motora aktaralım
      delay(1000);                    //1 saniye bekleyelim,  
      myservo.write(servopos);        //ve 1.servo motora aktaralım
      delay(5);                       //azıcık mola versinler...
    }
    else {
      myservo1.write(0);              // BT gelen veri 0 ve 90 değerlerinin dışında ise,
      myservo.write(0);               // iki servo da 0 pozisyonuna gelsinler. Else bloğu silinirse, o zaman sadece 0 ve 90 a tepki verir.
      delay(5);                       // azıcık mola versinler...
    }

    /*Servoları arduinodan ayrı Vcc kaynaktan beslemelisiniz!
       Aksi halde çalışmaz ya da gariplikler yapabilirler!
    */
  }
}
