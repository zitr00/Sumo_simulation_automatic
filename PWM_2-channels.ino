int n;
int a[3],d,i=0;

void setup()
{
  Serial.begin(9600);
cli();//oprire intreruperi
//initializari functii
T2();
sei();//pornire intreruperi
}

///Timere
void T2()
{
  TCCR2A = 0;//setarea valorilor registrului pe 0
  DDRB|=(1<<PB3);//OCR2A
  DDRD|=(1<<PD3);//OCR2B
  TCCR2A |= (1 << COM2B1) | (1<<COM2A1); //clear OC2B on match
  TCCR2A |= (1 << WGM21)|(1 << WGM20);//fast pwm
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);//prescaler
  OCR2B = 0;
  OCR2A= 0;
}

//semnal pwm
void PWM()
{
  //fade in
    for(int i=0; i<255*a[0]/100; i++)
    {
    	OCR2A =i;
   		 _delay_ms(2);
    }
    for(int i=0; i<255*a[1]/100; i++)
    {
    	OCR2B =i;
   		 _delay_ms(2);
    }
     for(int i=256*a[0]/100; i>0; i--)
    {
      OCR2A= i;
    	_delay_ms(2);
    }
    for(int i=256*a[1]/100; i>0; i--)
    {
      OCR2B= i;
    	_delay_ms(2);
    }
}

void tastatura()
{
  if(Serial.available())
  {
    while (Serial.available()) {
    d=Serial.parseInt(); //extragere numere din textul de la tastatura
    a[i]=d; //memorare valori PWM A si B
    i++;
  }
  i=0; //pentru introduceri de alte valori
  }
}

void loop() {
  tastatura();
  PWM();
}