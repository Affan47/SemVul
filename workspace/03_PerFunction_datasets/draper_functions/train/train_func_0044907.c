equalize_histo( void *in_data, int data_type, unsigned int totalPix,
                     double *min, double *max )
{
   unsigned int histo[MAX_LOOKUP], excess;
   int color, level, done;
   double bin, pixbin, lvl;
   int bottBin, topBin;
#if !(defined(__WIN32__) || defined(macintosh))
   int col,i,j;
   char *elem;
#endif


   done = 0;
   do {

      convert_block_to_histo(in_data, totalPix, data_type, min, max, histo);

      pixbin = (double)(totalPix - (totalPix>1?1:0)) / 256.0;
      if( pixbin>1.0 ) {


         pixbin *= 3.0;
         excess = 0;
         for( level=0; level<MAX_LOOKUP; level++ )
            if( histo[level]>pixbin ) {
               excess += (unsigned int)((histo[level]-pixbin-0.5));
               histo[level] = (unsigned int)(pixbin+0.5);
            }
         pixbin = (double)(totalPix - (totalPix>1?1:0) - excess) / 256.0;
         if( pixbin < 1.0 ) pixbin=1.0;
      }


      bin = 0.0;
      for( level=color=0; level<MAX_LOOKUP-1 && color<255; level++) {
         byteLookup[level] = color;
         bin += histo[level];
         while( bin>=pixbin && color<255 ) {
            bin -= pixbin;
            color++;
         }
      }
      while( level<MAX_LOOKUP ) byteLookup[level++] = 255;


      bottBin = topBin = -1;
      for( level=1; level<MAX_LOOKUP; level++ ) {
         if( bottBin < 0 && byteLookup[level] > 5   )
            bottBin = level-1;
         if( topBin  < 0 && byteLookup[level] > 250 )
            topBin = level;
      }
      if( topBin - bottBin < MAX_LOOKUP>>3 ) {
         if( bottBin > 0            ) bottBin--;
         if( topBin  < MAX_LOOKUP-1 ) topBin++;
         lvl = (*max-*min)/(MAX_LOOKUP-1.0);
         if( topBin-bottBin>2  ||  lvl>1e-6*fabs(*min) ) {
           *max = topBin  * lvl + *min;
           *min = bottBin * lvl + *min;
         } else
           done = 1;
      } else {
         done = 1;
      }

   } while( ! done );

}
