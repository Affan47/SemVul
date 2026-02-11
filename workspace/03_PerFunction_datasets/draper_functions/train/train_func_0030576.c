rm_del_from_lists()
  {
    register iptr  w, *list;
    int            vec_del;

    vec_del = mark_deleted_vectors();

    maxsequence = rm_from_seq( &slist );
    maxclock = rm_from_seq( &xclock );

    if( analyzerON ) RemoveAllDeleted();

    for( list = &wvlist; (w = *list) != NULL; )
      {
	if( ((bptr) (w->inode))->traced & DELETED )
	  {
	    *list = w->next;
	    FreeInput( w );
	  }
	else
	    list = &w->next;
      }

    for( list = &wlist; (w = *list) != NULL; )
      {
	if( w->inode->nflags & DELETED )
	  {
	    *list = w->next;
	    FreeInput( w );
	  }
	else
	  {
	    UnAlias( w->inode );
	    list = &w->next;
	  }
      }

    if( vec_del )
      {
	register bptr  b, *lst;

	for( lst = &blist; (b = *lst) != NULL; )
	  {
	    if( b->traced & DELETED )
	      {
		*lst = b->next;
		Vfree( b->name );
		Vfree( b );
	      }
	    else
		lst = &b->next;
	  }
      }
  }
