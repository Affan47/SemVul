SetFrequency(double Frequency,CText *p)
{
   unsigned char Khz;
   unsigned char TenKhz;
   unsigned char OnehundredKhz;
   unsigned char Mhz;
   double RoundedFreq;
   unsigned int frequency = (unsigned int) ((Frequency * 1e6) + .5);

   Khz = (frequency % 10000) / 1000;
   frequency /= 10000;
   TenKhz = frequency % 10;
   frequency /= 10;
   OnehundredKhz = frequency % 10;
   frequency /= 10;
   Mhz = frequency % 10;

   Data[2] &= 0xf0;
   Data[2] |= Mhz;

   if(Khz > 5) {
      frequency = (int) ((Frequency * 1e6) + .5);
      frequency = ((frequency / 10000) * 10000) + 5000;
      RoundedFreq = (double) frequency / 1e6;
      p->print("%lf rounded down to %3.3lf\n",Frequency,RoundedFreq);
      Data[2] |= 0x40;
   }
   else if(Khz == 5) {
      Data[2] |= 0x40;
   }
   else if(Khz != 0) {
      Data[2] &= ~0x40;
      frequency = (int) ((Frequency * 1e6) + .5);
      frequency = (frequency / 10000) * 10000;
      RoundedFreq = (double) frequency / 1e6;
      p->print("%lf rounded down to %3.3lf\n",Frequency,RoundedFreq);
   }
   else {
      Data[2] &= ~0x40;
   }

   Data[3] = TenKhz | (OnehundredKhz << 4);
}
