scope_extract_back(
            const char* scope,
   char*       back,
   char*       rest
) { PROFILE(SCOPE_EXTRACT_BACK);

  const char* ptr;
  char        endchar;

  ptr = scope + strlen( scope ) - 1;


  endchar = (*ptr == ' ') ? '\\' : '.';

  while( (ptr > scope) && (*ptr != endchar) ) {
    ptr--;
  }


  if( endchar == '\\' ) {
    while( (ptr > scope) && (*ptr != '.') ) {
      ptr--;
    }
  }

  strncpy( rest, scope, (ptr - scope) );
  rest[ (ptr - scope) ] = '\0';

  if( *ptr == '.' ) {
    ptr++;
  }

  strncpy( back, ptr, ((strlen( scope ) + scope) - ptr) );
  back[ ((strlen( scope ) + scope) - ptr) ] = '\0';

  PROFILE_END;

}
