ures_appendResPath(UResourceBundle *resB, const char* toAdd, int32_t lenToAdd, UErrorCode *status) {
    int32_t resPathLenOrig = resB->fResPathLen;
    if(resB->fResPath == NULL) {
        resB->fResPath = resB->fResBuf;
        *(resB->fResPath) = 0;
        resB->fResPathLen = 0;
    }
    resB->fResPathLen += lenToAdd;
    if(RES_BUFSIZE <= resB->fResPathLen+1) {
        if(resB->fResPath == resB->fResBuf) {
            resB->fResPath = (char *)uprv_malloc((resB->fResPathLen+1)*sizeof(char));

            if (resB->fResPath == NULL) {
                *status = U_MEMORY_ALLOCATION_ERROR;
                return;
            }
            uprv_strcpy(resB->fResPath, resB->fResBuf);
        } else {
            char *temp = (char *)uprv_realloc(resB->fResPath, (resB->fResPathLen+1)*sizeof(char));

            if (temp == NULL) {
                *status = U_MEMORY_ALLOCATION_ERROR;
                return;
            }
            resB->fResPath = temp;
        }
    }
    uprv_strcpy(resB->fResPath + resPathLenOrig, toAdd);
}
