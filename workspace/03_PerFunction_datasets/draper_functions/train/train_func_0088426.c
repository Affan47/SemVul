Add(Dlist *l,const void *elem)
{
    int r;
    if (elem == NULL || l == NULL) {
    	if (l)
    		l->RaiseError("iDlist.Add",CONTAINER_ERROR_BADARG);
    	else
    		iError.NullPtrError("iDlist.Add");
    	return CONTAINER_ERROR_BADARG;
    }
    if (l->Flags &CONTAINER_READONLY) {
    	l->RaiseError("iDlist.Add",CONTAINER_ERROR_READONLY,l);
    	return CONTAINER_ERROR_READONLY;
    }
    r = Add_nd(l,elem);
    if (r < 0)
    	return r;
    if (l->Flags & CONTAINER_HAS_OBSERVER)
    	iObserver.Notify(l,CCL_ADD,elem,NULL);

    return 1;
}
