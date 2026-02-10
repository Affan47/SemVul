wresist( list, w, l )
  register struct width  *list;
  int                    w, l;
  {
    register struct width  *p, *q;
    double                 size = ((double) l) / ((double) w);
    double                 temp;

    for( p = list, q = NULL; p != NULL; q = p, p = p->next )
      {
	if( p->w == w or( p->w > w and q == NULL ) )
	    return( lresist( p->list, l, size ) );
	if( p->w > w )
	  {
	    temp = lresist( q->list, l, size );
	    return( interp( w, q->w, temp, p->w, lresist( p->list, l, size ) ) );
	  }
      }
    if( q != NULL )
	return( lresist( q->list, l, size ) );
    return( 1E4 * size );
  }
