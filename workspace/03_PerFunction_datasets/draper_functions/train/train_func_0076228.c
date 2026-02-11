cnfImprta( const char *source_f, int source_len, char *dest_c,
                 int dest_len, int ndims, const int *dims )


{


   int i;
   int nels;
   int el;
   int foffset;
   int coffset;


   nels = 1;
   for ( i=0; i<ndims; i++ ) {
       nels *= *(dims+i);
   }


   foffset = 0;
   coffset = 0;
   for( el=0; el<nels; el++){


      for(
      i = source_len - 1; ( i >= 0 ) && ( *(source_f+foffset+i) == ' ' ); i-- )
      ;


      if ( i < (dest_len-1) ) {
         *(dest_c+coffset+i+1) = '\0';
      } else {
         i = dest_len-1;
      }


      for(  ; i >= 0 ; i-- )
         *(dest_c+coffset+i) = *(source_f+foffset+i);


      foffset += source_len;
      coffset += dest_len;
   }
}
