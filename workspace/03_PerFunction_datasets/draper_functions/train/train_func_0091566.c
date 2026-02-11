shallowTextClone(UText * dest, const UText * src, UErrorCode * status) {
    if (U_FAILURE(*status)) {
        return NULL;
    }
    int32_t  srcExtraSize = src->extraSize;


    dest = utext_setup(dest, srcExtraSize, status);
    if (U_FAILURE(*status)) {
        return dest;
    }


    void *destExtra = dest->pExtra;
    int32_t flags   = dest->flags;


    int sizeToCopy = src->sizeOfStruct;
    if (sizeToCopy > dest->sizeOfStruct) {
        sizeToCopy = dest->sizeOfStruct;
    }
    uprv_memcpy(dest, src, sizeToCopy);
    dest->pExtra = destExtra;
    dest->flags  = flags;
    if (srcExtraSize > 0) {
        uprv_memcpy(dest->pExtra, src->pExtra, srcExtraSize);
    }


    adjustPointer(dest, &dest->context, src);
    adjustPointer(dest, &dest->p, src);
    adjustPointer(dest, &dest->q, src);
    adjustPointer(dest, &dest->r, src);
    adjustPointer(dest, (const void **)&dest->chunkContents, src);


    dest->providerProperties &= ~I32_FLAG(UTEXT_PROVIDER_OWNS_TEXT);

    return dest;
}
