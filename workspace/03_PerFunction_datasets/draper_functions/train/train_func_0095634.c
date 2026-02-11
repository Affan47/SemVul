EnterAlias( n, nd )
  register int  n;
  nptr          nd;
  {
    register int   i;
    register nptr  *tbl;

    i = AliasTblBucket( n );
    if( i >= aliases.size )
	IncreaseAliasTbl( i );

    if( (tbl = aliases.bucket[ i ]) == NULL )
      {
	register nptr  *t, *t_end;

	tbl = (nptr *) Valloc( SIZEOF( nptr ) * ALIAS_TBL_SIZE, 1 );
	aliases.bucket[ i ] = tbl;
	for( t = tbl, t_end = t + ALIAS_TBL_SIZE; t < t_end; *t++ = NULL );
      }

    tbl[ AliasTblIndex( n ) ] = nd;
  }
