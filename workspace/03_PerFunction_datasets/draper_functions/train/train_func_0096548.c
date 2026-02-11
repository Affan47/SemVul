PopBack(Dlist *l,void *result)
{
    DlistElement *le;

    if (l == NULL) return iError.NullPtrError("iDlist.PopBack");

    if (l->count == 0)
    	return 0;
    if (l->Flags & CONTAINER_READONLY) {
    	l->RaiseError("iDlist.PopBack",CONTAINER_ERROR_READONLY,l);
    	return CONTAINER_ERROR_READONLY;
    }
    le = l->Last;
    if (l->count == 1) {
    	l->First = l->Last = NULL;
    }
    else {
    	l->Last = le->Previous;
    	l->Last->Next = NULL;
    }
    l->count--;
    if (result)
    	memcpy(result,&le->Data,l->ElementSize);
    le->Next = l->FreeList;
    l->FreeList = le;
    l->timestamp++;
    return 1;
}
