InitRankFileBit (void)


{
   BitBoard b;
   int i;

   i = 8;
   b = (BitBoard) 255;
   while (i--)
   {
      RankBit[i] = b;
      b <<= 8;
   }

   i = 8;
   b = ULL(0x0101010101010101);
   while (i--)
   {
      FileBit[i] = b;
      b <<= 1;
   }
}
