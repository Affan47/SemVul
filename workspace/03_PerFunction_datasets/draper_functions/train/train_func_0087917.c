xdll_reopen (int newflag,void * beg,int nlinks,int newhead)


#ifdef DOC
int	        newflag  ;

void *		beg       ;

int             nlinks    ;

int     	newhead   ;

#endif


{
  int old_nlinks,delta;
  xdllink *curr;
  int oldhead;
  int retval = FUNCBAD;

  CHECKUSE;
  if(xdllist_curr->head != NULL)
    oldhead = SUBBEG(xdllist_curr->head);
  old_nlinks = xdllist_curr->nlinks;
  if (beg  != NULL) xdllist_curr->beg = (xdllink *) beg;
  if (nlinks > 0) xdllist_curr->nlinks = nlinks;

  curr = (newflag) ? NULL :
         ((newhead >= 0) ? ADDBEG(newhead) :
	 ((xdllist_curr->head == NULL) ? NULL : ADDBEG(oldhead)) );


  if (curr != NULL && curr->prev != HEADID)
     goto error_return;
  xdllist_curr->head = xdllist_curr->curr = curr;


  delta = xdllist_curr->nlinks - old_nlinks;
  if (delta > 0)
  {
    curr = ADDBEG( (old_nlinks * xdllist_curr->size) );

    clear_links(curr,delta,NULL);
  }
    retval = FUNCOK;
error_return:
    return (retval);
}
