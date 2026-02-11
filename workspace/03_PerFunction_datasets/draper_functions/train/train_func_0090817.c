IRandomX(int min, int max) {


   if (max <= min) {
      if (max == min) return min; else return 0x80000000;
   }
#ifdef  INT64_DEFINED

   uint32 interval;
   uint64 longran;
   uint32 iran;
   uint32 remainder;

   interval = uint32(max - min + 1);
   if (interval != LastInterval) {


      RLimit = uint32(((uint64)1 << 32) / interval) * interval - 1;
      LastInterval = interval;
   }
   do {
      longran  = (uint64)BRandom() * interval;
      iran = (uint32)(longran >> 32);
      remainder = (uint32)longran;
   } while (remainder > RLimit);

   return (int32)iran + min;

#else

   uint32 interval;
   uint32 bran;
   uint32 iran;
   uint32 remainder;

   interval = uint32(max - min + 1);
   if (interval != LastInterval) {


      RLimit = (uint32)0xFFFFFFFF / interval;
      if ((uint32)0xFFFFFFFF % interval == interval - 1) RLimit++;
   }
   do {
      bran = BRandom();
      iran = bran / interval;
      remainder = bran % interval;
   } while (iran >= RLimit);

   return (int32)remainder + min;

#endif
}
