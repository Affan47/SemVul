RemoveRange(Dlist *l,size_t start, size_t end)
{
    DlistElement *rvp,*rvpS,*rvpE;
    size_t position=0,tmp;

    if (l == NULL) {
        iError.RaiseError("RemoveRange",CONTAINER_ERROR_BADARG);
        return CONTAINER_ERROR_BADARG;
    }
    if (l->Flags&CONTAINER_READONLY) {
        l->RaiseError("RemoveRange",CONTAINER_ERROR_READONLY,l);
        return CONTAINER_ERROR_READONLY;
    }
    rvp = l->First;
    if (start >= l->count)
        return 0;
    if (end >= l->count)
        end = l->count;
    if (start == end) return 0;
    if (end < start) {
        tmp = end;
        end = start;
        start = tmp;
    }
    while (rvp && position != start) {
        rvp = rvp->Next;
        position++;
    }
    if (rvp == NULL) {
        l->RaiseError("RemoveRange",CONTAINER_INTERNAL_ERROR);
        return CONTAINER_INTERNAL_ERROR;
    }
    rvpS = rvp->Previous;
    while (rvp && position < end) {
        rvp = rvp->Next;
        position++;
    }
    if (rvp == NULL) {
        iError.RaiseError("RemoveRange",CONTAINER_ASSERTION_FAILED);
        return CONTAINER_ASSERTION_FAILED;
    }
    rvpE = rvp->Previous;
    if (rvpS) {
        if (rvpE) {
            rvpS->Next = rvpE;
            rvpE->Previous = rvpS;
        }
        else rvpS->Next = NULL;
    }
    if (start == 0) {
        l->First = rvpE;
        if (rvpE)
            rvpE->Previous = NULL;
    }
    if (end == l->count-1) {
        l->Last = rvpE;
        if (rvpE)
            rvpE->Next = NULL;
    }
    l->count -= (end-start-1);
    l->timestamp++;
    return 1;
}
