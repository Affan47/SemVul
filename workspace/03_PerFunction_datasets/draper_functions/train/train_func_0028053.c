append_extension( char *s, char *ext, int mode )
#else
append_extension( s, ext, mode )
     char *s, *ext;
     int mode;
#endif
   {
   int i, len;
   char *newname;
#ifdef OPTION_PREFIX_SLASH

   for ( len = 0; s[len] != '\0' && s[len] != '/'; len++ )
      continue;
#else
   len = ( unsigned ) strlen( s );
#endif


   for ( i = len - 1; i > 0; i-- )
      {
      if ( s[i] == '.'
#ifdef UNIX
           || s[i] == '/'
#endif
#ifdef VMS
           || s[i] == ']' || s[i] == ':'
#endif
#ifdef MSDOS
           || s[i] == '\\' || s[i] == ':'
#endif
          )
         break;
      }

   if ( mode == MODE_REPLACE_EXT )
      {
      if ( s[i] == '.' )
         len = i;
      newname =
         ( char * )
         malloc( ( unsigned ) ( len + ( unsigned ) strlen( ext ) + 1 ) );
      ( void ) strncpy( newname, s, len );
      ( void ) strcpy( newname + len, ext );
      }
   else
      {
#ifdef OPTION_PREFIX_SLASH


      if ( s[i] != '.' || s[len] != '\0' )
         {
         if ( s[i] != '.' )
            {
            newname = ( char * ) malloc( ( unsigned ) ( len +
                                                        ( unsigned ) strlen( ext )
                                                        + 1 ) );
            ( void ) strncpy( newname, s, len );
            ( void ) strcpy( newname + len, ext );
            }
         else
            {

            newname = ( char * ) malloc( ( unsigned ) ( len + 1 ) );
            ( void ) strncpy( newname, s, len );
            }
         }
#else
      if ( s[i] != '.' )
         {
         newname = ( char * ) malloc( ( unsigned ) ( len +
                                                     ( unsigned ) strlen( ext ) +
                                                     1 ) );
         ( void ) strcpy( newname, s );
         ( void ) strcat( newname, ext );
         }
#endif
      else
         {
         newname = s;
         }
      }

   return newname;
   }
