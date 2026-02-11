loadData(UResourceBundle* rb, const char* key, UBool& shortCommonlyUsed) {
    if (rb == NULL || key == NULL || *key == 0) {
        return NULL;
    }

    UErrorCode status = U_ZERO_ERROR;
    const UChar **names = NULL;

    UResourceBundle* rbTable = NULL;
    rbTable = ures_getByKeyWithFallback(rb, key, rbTable, &status);
    if (U_SUCCESS(status)) {
        names = (const UChar **)uprv_malloc(sizeof(const UChar*) * KEYS_SIZE);
        if (names != NULL) {
            UBool isEmpty = TRUE;
            for (int32_t i = 0; i < KEYS_SIZE; i++) {
                status = U_ZERO_ERROR;
                int32_t len = 0;
                const UChar *value = ures_getStringByKeyWithFallback(rbTable, KEYS[i], &len, &status);
                if (U_FAILURE(status) || len == 0) {
                    names[i] = NULL;
                } else {
                    names[i] = value;
                    isEmpty = FALSE;
                }
            }
            if (isEmpty) {

                uprv_free(names);
                names = NULL;
            }
        }

        if (names != NULL) {
            status = U_ZERO_ERROR;
            UResourceBundle* cuRes = ures_getByKeyWithFallback(rbTable, gCuTag, NULL, &status);
            int32_t cu = ures_getInt(cuRes, &status);
            if (U_SUCCESS(status)) {
                shortCommonlyUsed = (cu != 0);
            }
            ures_close(cuRes);
        }
    }
    ures_close(rbTable);
    return names;
}
