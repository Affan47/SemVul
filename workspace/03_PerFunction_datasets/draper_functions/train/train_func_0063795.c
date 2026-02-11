cnfExprta( const char *source_c, int source_len, char *dest_f,
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
      for( i = 0 ; (i < dest_len ) && ( *(source_c+coffset+i) != '\0' ) ; i++ )
         *(dest_f+foffset+i) = *(source_c+coffset+i);


      for(  ; i < dest_len ; i++ )
         *(dest_f+foffset+i) = ' ';


      foffset += dest_len;
      coffset += source_len;
   }
}
