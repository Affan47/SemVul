InsertIn(Vector *AL, size_t idx, Vector *newData)
{
    size_t newCount;
    char *p;

    if (AL == NULL) {
        return NullPtrError("InsertIn");
    }
    if (newData == NULL) {
        AL->RaiseError("InsertIn",CONTAINER_ERROR_BADARG);
        return CONTAINER_ERROR_BADARG;
    }
    if (AL->Flags & CONTAINER_READONLY)
        return ErrorReadOnly(AL,"InsertIn");
    if (idx > AL->count) {
        AL->RaiseError("iVector.InsertIn",CONTAINER_ERROR_INDEX,AL,idx);
        return CONTAINER_ERROR_INDEX;
    }
    if (AL->ElementSize != newData->ElementSize) {
        return ErrorIncompatible(AL,"InsertIn");
    }
    newCount = AL->count + newData->count;
    if (newCount >= (AL->capacity-1)) {
        int r = ResizeTo(AL,newCount);
        if (r <= 0)
            return r;
    }
    p = (char *)AL->contents;
    if (idx < AL->count) {
        memmove(p+AL->ElementSize*(idx+newData->count),
                p+AL->ElementSize*idx,
                (AL->count-idx)*AL->ElementSize);
    }
    p += idx*AL->ElementSize;
    memcpy(p,newData->contents,newData->ElementSize*newData->count);
    AL->timestamp++;
    AL->count = newCount;
    if (AL->Flags & CONTAINER_HAS_OBSERVER)
        iObserver.Notify(AL,CCL_INSERT_IN,newData,NULL);
    return 1;
}
