compat_SyncMutableUTextContents(UText *ut) {
    UBool retVal = FALSE;


    if (utext_nativeLength(ut) != ut->nativeIndexingLimit) {
        UnicodeString *us=(UnicodeString *)ut->context;


        int32_t newLength = us->length();


        ut->chunkContents    = us->getBuffer();
        ut->chunkLength      = newLength;
        ut->chunkNativeLimit = newLength;
        ut->nativeIndexingLimit = newLength;
        retVal = TRUE;
    }

    return retVal;
}
