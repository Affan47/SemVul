walk_trans( func, arg )
  void  (*func)();
  char  *arg;
  {
    register int   index;
    register tptr  t;

    for( index = 0; index < HASHSIZE; index++ )
      {
	for( t = tpostbl[ index ]; t != NULL; t = t->tlink )
	    (*func)( t, arg );
      }

    if( other_t != NULL )
      {
	for( t = other_t->x.ptr; t != other_t; t = t->x.ptr )
	    (*func)( t, arg );
      }
  }
