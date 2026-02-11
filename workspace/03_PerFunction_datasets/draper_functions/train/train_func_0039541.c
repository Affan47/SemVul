str_end_strip(
   char *str )
#else
 str_end_strip( str )
   char *str;
#endif
   {
   int len;

   if ( str == NULL ) return( str );

   len = strlen( str ) - 1;
   while ( len >= 0 && str[len] == ' ' ) { str[len] = '\0'; len--; }
   return( str );
   }
