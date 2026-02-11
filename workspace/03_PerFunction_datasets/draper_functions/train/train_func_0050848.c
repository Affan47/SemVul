winsert( list, w, l, resist )
  register struct width  **list;
  long                   w, l;
  double                 resist;
  {
    register struct width   *p, *q, *wnew;
    register struct length  *lnew;

    for( p = *list, q = NULL; p != NULL; q = p, p = p->next )
      {
	if( p->w == w )
	  {
	    linsert( &p->list, l, resist );
	    return;
	  }
	if( p->w > w )
	    break;
      }
    wnew = (struct width *) Valloc( sizeof( struct width ), 1 );
    lnew = (struct length *) Valloc( sizeof( struct length ), 1 );
    wnew->next = p;
    wnew->list = lnew;
    wnew->w = w;
    if( q == NULL )
	*list = wnew;
    else
	q->next = wnew;
    lnew->next = NULL;
    lnew->l = l;
    lnew->r = resist;
  }
