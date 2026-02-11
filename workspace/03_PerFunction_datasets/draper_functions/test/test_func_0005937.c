SearchWithKey(Vector *vec,size_t startByte,size_t sizeKey,size_t startidx,void *item,size_t *result)
{
    size_t i;
    char *p;

    if (vec == NULL || result == NULL) {
        return NullPtrError("SearchWithKey");
    }
    if (startByte >= vec->ElementSize) {
        return 0;
    }
    if (sizeKey >= (vec->ElementSize-startByte))
        sizeKey = vec->ElementSize-startByte;
    if (startidx >= vec->count)
        return 0;
    p = vec->contents;
    for (i=startidx; i<vec->count; i++) {
        if (memcmp(p+startByte,item,sizeKey) == 0) {
            *result = i;
            return 1;
        }
        p += vec->ElementSize;
    }
    return 0;
}
