utf8TextExtract(UText *ut,
                int64_t start, int64_t limit,
                UChar *dest, int32_t destCapacity,
                UErrorCode *pErrorCode) {
    if(U_FAILURE(*pErrorCode)) {
        return 0;
    }
    if(destCapacity<0 || (dest==NULL && destCapacity>0)) {
        *pErrorCode=U_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }
    int32_t  length  = ut->b;
    int32_t  start32 = pinIndex(start, length);
    int32_t  limit32 = pinIndex(limit, length);

    if(start32>limit32) {
        *pErrorCode=U_INDEX_OUTOFBOUNDS_ERROR;
        return 0;
    }


    const uint8_t *buf = (const uint8_t *)ut->context;
    int i;
    if (start32 < ut->chunkNativeLimit) {
        for (i=0; i<3; i++) {
            if (U8_IS_SINGLE(buf[start32]) || U8_IS_LEAD(buf[start32]) || start32==0) {
                break;
            }
            start32--;
        }
    }

    if (limit32 < ut->chunkNativeLimit) {
        for (i=0; i<3; i++) {
            if (U8_IS_SINGLE(buf[limit32]) || U8_IS_LEAD(buf[limit32]) || limit32==0) {
                break;
            }
            limit32--;
        }
    }


    int32_t destLength=0;
    utext_strFromUTF8(dest, destCapacity, &destLength,
                    (const char *)ut->context+start32, limit32-start32,
                    pErrorCode);
    utf8TextAccess(ut, limit32, TRUE);
    return destLength;
}
