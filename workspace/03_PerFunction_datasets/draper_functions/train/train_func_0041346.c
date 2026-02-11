idelete( n, list )
  register nptr  n;
  register iptr  *list;
  {
    register iptr  p = *list;
    register iptr  q;

    if( p == NULL )
	return;
    else if( p->inode == n )
      {
	*list = p->next;
	FreeInput( p );
      }
    else
      {
	for( q = p->next; q != NULL; p = q, q = p->next )
	    if( q->inode == n )
	      {
		p->next = q->next;
		FreeInput( q );
		return;
	      }
      }
  }
