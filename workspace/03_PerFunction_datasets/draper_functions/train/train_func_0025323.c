doUntil( )
  {
    char      *mask, *value, *name;
    Find1Arg  f;
    int i, nbits, ccount, cnt = 0, comp = 0;
    nptr *nodes;

    if( targc == 5 )
      {
	mask = targv[2];
	value = targv[3];
        ccount = atoi(targv[4]);
      }
    else
      {
	mask = NULL;
	value = targv[2];
        ccount = atoi(targv[3]);
      }

    FindOne( &f );

    if( f.num > 1 )
	rsimerror( filename, lineno, "%s matches more than one node or vector\n",
	  targv[1] );
    else if( f.node != NULL )
      {
	name = pnode( f.node );
	UnAlias( f.node );
        targc = 1;
	while((cnt <= ccount) && (comp = CompareVector( &f.node, name, 1, mask, value ) != 0)) {
            cnt++;
            clockit(1); }
        nodes = &f.node;
        nbits = 1;
      }
    else if( f.vec != NULL ) {
        targc = 1;
	while((cnt <= ccount) && (comp = CompareVector( f.vec->nodes, f.vec->name, f.vec->nbits, mask,
            value ) != 0)) {
            cnt++;
            clockit(1); }
        name = f.vec->name;
        nbits = f.vec->nbits;
        nodes = f.vec->nodes; }
    if(comp != 0) {
        lprintf( stderr, "(%s, %d): assertion failed on '%s' ",
         filename, lineno, name );
        for( i = 0; i < nbits; i++ )
          {
     	    if( mask != NULL and mask[i] != '0' )
	      {
	       lprintf( stdout, "-" );
	       value[i] = '-';
	      }
	   else
	       lprintf( stdout, "%c", vchars[ nodes[i]->npot ] );
          }
        lprintf( stdout, " (%s)\n", value );
        }
    return( 0 );
  }
