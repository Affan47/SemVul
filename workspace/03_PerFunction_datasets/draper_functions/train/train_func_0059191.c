cnfCreim( const char *source_f, int source_len )


{


   int i;
   char *ptr;


   for( i = source_len - 1 ; ( i >= 0 ) && ( source_f[i] == ' ' ) ; i-- )
      ;


   ptr = (char *)malloc( (size_t)( i + 2 ) );


   if( ptr != 0 )
   {
      ptr[i+1] = '\0';

      for(  ; i >= 0 ; i-- )
         ptr[i] = source_f[i];
   }

   return( ptr );
}
