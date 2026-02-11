str_match( p, s )
  register char  *p, *s;
  {
    while( 1 )
      {
	if( *p == '*' )
	  {

	    do
		p++;
	    while( *p == '*' );


	    if( *p == 0 )
		return( 1 );


	    while( *s != 0 )
	      {
		while( lcase[(int)*s] != lcase[(int)*p] )
		    if( *s++ == 0 )
			return( 0 );
		if( str_match( p + 1, ++s ) )
		    return( 1 );
	      }


	    return( 0 );
	  }
	else if( *p == 0 )
	    return( *s == 0 );
	else if( lcase[(int)*p++] != lcase[(int)*s++] )
	    return( 0 );
      }
  }
