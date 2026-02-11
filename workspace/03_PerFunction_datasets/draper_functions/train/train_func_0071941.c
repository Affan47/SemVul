readData(
         int   inCount,
         short inArray[],
         short *outPtr[],
         int   dataArraySize,
         int   Xoff,
         bool  init_count)
{
   int    i, Nsamps, c;
   static unsigned int framecount;
   short *ptr;

   if (init_count == TRUE)
      framecount = 0;

   Nsamps = dataArraySize - Xoff;


   if (Nsamps > (inCount - (int)framecount))
   {
      Nsamps = inCount - framecount;
   }

   for (c = 0; c < _nChans; c++)
   {
      ptr = outPtr[c];
      ptr += Xoff;

      for (i = 0; i < Nsamps; i++)
         *ptr++ = (short) inArray[c * inCount + i + framecount];
   }

   framecount += Nsamps;

   if ((int)framecount >= inCount)
      return (((Nsamps - (framecount - inCount)) - 1) + Xoff);
   else
      return 0;
}
