_ldmlKeyToBCP47(const char* key, int32_t keyLen,
                char* bcpKey, int32_t bcpKeyCapacity,
                UErrorCode *status) {
    UResourceBundle *rb;
    char keyBuf[MAX_LDML_KEY_LEN];
    char bcpKeyBuf[MAX_BCP47_SUBTAG_LEN];
    int32_t resultLen = 0;
    int32_t i;
    UErrorCode tmpStatus = U_ZERO_ERROR;
    const UChar *uBcpKey;
    int32_t bcpKeyLen;

    if (keyLen < 0) {
        keyLen = (int32_t)uprv_strlen(key);
    }

    if (keyLen >= sizeof(keyBuf)) {

        *status = U_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }

    uprv_memcpy(keyBuf, key, keyLen);
    keyBuf[keyLen] = 0;


    for (i = 0; i < keyLen; i++) {
        keyBuf[i] = uprv_tolower(keyBuf[i]);
    }

    rb = ures_openDirect(NULL, KEYTYPEDATA, status);
    ures_getByKey(rb, KEYMAP, rb, status);

    if (U_FAILURE(*status)) {
        ures_close(rb);
        return 0;
    }

    uBcpKey = ures_getStringByKey(rb, keyBuf, &bcpKeyLen, &tmpStatus);
    if (U_SUCCESS(tmpStatus)) {
        u_UCharsToChars(uBcpKey, bcpKeyBuf, bcpKeyLen);
        bcpKeyBuf[bcpKeyLen] = 0;
        resultLen = bcpKeyLen;
    } else {
        if (_isLDMLKey(key, keyLen)) {
            uprv_memcpy(bcpKeyBuf, key, keyLen);
            bcpKeyBuf[keyLen] = 0;
            resultLen = keyLen;
        } else {

            *status = U_ILLEGAL_ARGUMENT_ERROR;
        }
    }
    ures_close(rb);

    if (U_FAILURE(*status)) {
        return 0;
    }

    uprv_memcpy(bcpKey, bcpKeyBuf, uprv_min(resultLen, bcpKeyCapacity));
    return u_terminateChars(bcpKey, bcpKeyCapacity, resultLen, status);
}
