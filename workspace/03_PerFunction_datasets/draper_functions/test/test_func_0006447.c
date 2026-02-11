loadData(UResourceBundle* rb, const char* key) {
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
    }
    ures_close(rbTable);
    return names;
}
