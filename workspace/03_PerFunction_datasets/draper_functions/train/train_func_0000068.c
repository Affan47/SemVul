createInstance(const Locale & inLocale, UErrorCode& status) {

    if (U_FAILURE(status)) {
        return NULL;
    }

    UBool nsResolved = TRUE;
    UBool usingFallback = FALSE;
    char buffer[ULOC_KEYWORDS_CAPACITY];
    int32_t count = inLocale.getKeywordValue("numbers",buffer, sizeof(buffer),status);
    if ( count > 0 ) {
        buffer[count] = '\0';
        if ( !uprv_strcmp(buffer,gDefault) || !uprv_strcmp(buffer,gNative) ||
             !uprv_strcmp(buffer,gTraditional) || !uprv_strcmp(buffer,gFinance)) {
            nsResolved = FALSE;
        }
    } else {
        uprv_strcpy(buffer,gDefault);
        nsResolved = FALSE;
    }

    if (!nsResolved) {
        UErrorCode localStatus = U_ZERO_ERROR;
        UResourceBundle *resource = ures_open(NULL, inLocale.getName(), &localStatus);
        UResourceBundle *numberElementsRes = ures_getByKey(resource,gNumberElements,NULL,&localStatus);
        while (!nsResolved) {
            localStatus = U_ZERO_ERROR;
            count = 0;
            const UChar *nsName = ures_getStringByKeyWithFallback(numberElementsRes, buffer, &count, &localStatus);
            if ( count > 0 && count < ULOC_KEYWORDS_CAPACITY ) {
                u_UCharsToChars(nsName,buffer,count);
                buffer[count] = '\0';
                nsResolved = TRUE;
            }

            if (!nsResolved) {
                if (!uprv_strcmp(buffer,gNative) || !uprv_strcmp(buffer,gFinance)) {
                    uprv_strcpy(buffer,gDefault);
                } else if (!uprv_strcmp(buffer,gTraditional)) {
                    uprv_strcpy(buffer,gNative);
                } else {
                    usingFallback = TRUE;
                    nsResolved = TRUE;
                }
            }
        }
        ures_close(numberElementsRes);
        ures_close(resource);
    }

    if (usingFallback) {
        status = U_USING_FALLBACK_WARNING;
        NumberingSystem *ns = new NumberingSystem();
        return ns;
    } else {
        return NumberingSystem::createInstanceByName(buffer,status);
    }
 }
