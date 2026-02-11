gifti_clear_float_zeros( char * str )
{
   char * dp, * valp;
   int    len;

   if( !str || !*str ) return 0;

   dp  = strchr(str, '.');
   if( !dp ) return 0;

   len = strlen(dp);


   for( valp = dp+len-1; (valp > dp+1) && (*valp==' ' || *valp=='0'); valp-- )
       *valp = '\0';

   if( valp < dp + len - 1 ) return 1;

   return 0;
}
