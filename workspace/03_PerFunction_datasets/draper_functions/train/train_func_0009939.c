psString( s, len )
  char  *s;
  int   len;
  {
    putc( '(', psout );
    while( *s != '\0' and len != 0 )
      {
	if( (*s == '(' ) || (*s == ')') )
	    putc( '\\', psout );
        putc( *s, psout );
	s++;
	len--;
      }
    putc( ')', psout );
  }
