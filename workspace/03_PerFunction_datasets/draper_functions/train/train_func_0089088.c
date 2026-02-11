InitBitPosArray (void)


{
   BitBoard b;
   int i;

   b = (BitBoard) 1;
   for (i = 63; i >= 0; i--, b <<= 1)
   {
      BitPosArray[i] = b;
      NotBitPosArray[i] = ~b;
   }
}
