BarcodeIRQHook(int a)
{
 BandaiIRQHook(a);

 BarcodeCycleCount+=a;

 if(BarcodeCycleCount >= 1000)
 {
  BarcodeCycleCount -= 1000;
  if(BarcodeData[BarcodeReadPos]==0xFF)
  {
   BarcodeOut=0;
  }
  else
  {
   BarcodeOut=(BarcodeData[BarcodeReadPos]^1)<<3;
   BarcodeReadPos++;
  }
 }
}
