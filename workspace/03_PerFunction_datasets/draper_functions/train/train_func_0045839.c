PopBack(Vector *AL,void *result)
{
    char *p;

    if (AL == NULL) {
    return CONTAINER_ERROR_BADARG;
    }
    if (AL->Flags&CONTAINER_READONLY) {
        return ErrorReadOnly(AL,"PopBack");
    }
    if (AL->count == 0)
        return 0;
    if (result) {
    p = AL->contents;
    p += AL->ElementSize*(AL->count-1);
    memcpy(result,p,AL->ElementSize);
    }
    AL->count--;
    AL->timestamp++;
    return 1;
}
