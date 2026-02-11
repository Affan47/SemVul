CleanEvents( n )
  register nptr  n;
  {
    register evptr  ev;

    do
      {
	while( (ev = n->events) != NULL )
	    PuntEvent( n, ev );
      }
    while( (n = n->nlink) != NULL );
  }
