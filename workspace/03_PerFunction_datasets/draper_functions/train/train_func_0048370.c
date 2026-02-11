Ns_ListSort(Ns_List *wPtr, Ns_SortProc *sortProc)
{
    Ns_List  *curPtr, *mPtr, *nPtr;
    Ns_List  *axisnodePtr;
    void     *axisPtr;
    Ns_List **lastmPtrPtr, **lastnPtrPtr;

    if ((wPtr == NULL) || (wPtr->rest == NULL)) {
        return wPtr;
    }

    curPtr = wPtr->rest;

    axisnodePtr = wPtr;
    axisnodePtr->rest = NULL;
    axisPtr = wPtr->first;

    mPtr = NULL;
    nPtr = NULL;

    lastmPtrPtr = &mPtr;
    lastnPtrPtr = &nPtr;
    while (curPtr != NULL) {
        if ((*sortProc) (curPtr->first, axisPtr) <= 0) {
            *lastmPtrPtr = curPtr;
            lastmPtrPtr = &(curPtr->rest);
        } else {
            *lastnPtrPtr = curPtr;
            lastnPtrPtr = &(curPtr->rest);
        }
        curPtr = curPtr->rest;
    }
    *lastmPtrPtr = NULL;
    *lastnPtrPtr = NULL;

    Ns_ListNconc(axisnodePtr, Ns_ListSort(nPtr, sortProc));
    return (Ns_ListNconc(Ns_ListSort(mPtr, sortProc), axisnodePtr));
}
