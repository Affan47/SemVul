Append(List * l1, List * l2)
{


    if (l1 == NULL || l2 == NULL) {
        if (l1)
            l1->RaiseError("iList.Append", CONTAINER_ERROR_BADARG);
        else
            iError.RaiseError("iList.Append", CONTAINER_ERROR_BADARG);
        return CONTAINER_ERROR_BADARG;
    }
    if ((l1->Flags & CONTAINER_READONLY) || (l2->Flags & CONTAINER_READONLY)) {
        return ErrorReadOnly(l1,"Append");
        return CONTAINER_ERROR_READONLY;
    }
    if (l2->ElementSize != l1->ElementSize || l2->Allocator != l1->Allocator) {
        l1->RaiseError("iList.Append", CONTAINER_ERROR_INCOMPATIBLE,l1,l2);
        return CONTAINER_ERROR_INCOMPATIBLE;
    }

    if (l1->Flags & CONTAINER_HAS_OBSERVER)
        iObserver.Notify(l1, CCL_APPEND, l2, NULL);

    if (l2->Flags & CONTAINER_HAS_OBSERVER)
        iObserver.Notify(l2, CCL_FINALIZE, NULL, NULL);

    if (l1->count == 0) {
        l1->First = l2->First;
        l1->Last = l2->Last;
    } else if (l2->count > 0) {
        if (l2->First)
            l1->Last->Next = l2->First;
        if (l2->Last)
            l1->Last = l2->Last;
    }
    l1->count += l2->count;
    l1->timestamp++;

    l2->Allocator->free(l2);
    return 1;
}
