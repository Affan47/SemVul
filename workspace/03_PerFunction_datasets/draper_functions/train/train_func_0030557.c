expand( string, buffer, bufsize, wc )
  char  	*string;
  char          **buffer;
  int           *bufsize;
  char          wc;
  {
    register char  *p;
    char           prefix[100], index[256];
    int            start, stop, nstep, length;


    p = prefix;
    length = 0;
    while( *string )
      {
	if( *string == ITERATOR_START )
	  {
	    *p = 0;
	    goto gotit;
	  }
	*p++ = *string++;
      }
    *p = 0;


    length = strlen( prefix ) + 1;
    if( length > *bufsize )
      {
	rsimerror( filename, lineno, "too many arguments in command\n" );
	return( 1 );
      }
    (void) strcpy( *buffer, prefix );
    wildCard[targc] = wc;
    targv[targc++] = *buffer;
    *bufsize -= length;
    *buffer += length;
    return( 0 );


  gotit :
    start = 0;
    stop = 0;
    nstep = 0;
    for( string += 1; *string >= '0' and *string <= '9'; string += 1 )
	start = start * 10 + *string - '0';
    if( *string != ':' )
	goto err;
    for( string += 1; *string >= '0' and *string <= '9'; string += 1 )
	stop = stop * 10 + *string - '0';
    if( *string == ITERATOR_END )
	goto done;
    if( *string != ':' )
	goto err;
    for( string += 1; *string >= '0' and *string <= '9'; string += 1 )
	nstep = nstep * 10 + *string - '0';
    if( *string == ITERATOR_END )
	goto done;

  err :
    rsimerror( filename, lineno, "syntax error in name iterator" );
    return( 1 );

  done :
    string += 1;


    if( nstep == 0 )
	nstep = 1;
    else if( nstep < 0 )
	nstep = -nstep;
    if( start > stop )
	nstep = -nstep;


    while( (nstep > 0 and start <= stop) or (nstep < 0 and start >= stop) )
      {
	(void) sprintf( index, "%s%d%s", prefix, start, string );
	if( expand( index, buffer, bufsize, wc ) )
	    return( 1 );
	start += nstep;
      }
    return( 0 );
  }
