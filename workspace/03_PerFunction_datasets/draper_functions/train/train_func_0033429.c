getCollationKey(const UChar* source,
                                                    int32_t sourceLen,
                                                    CollationKey& sortkey,
                                                    UErrorCode& status) const
{
    if (U_FAILURE(status)) {
        return sortkey.setToBogus();
    }
    if (sourceLen < -1 || (source == NULL && sourceLen != 0)) {
        status = U_ILLEGAL_ARGUMENT_ERROR;
        return sortkey.setToBogus();
    }

    if (sourceLen < 0) {
        sourceLen = u_strlen(source);
    }
    if (sourceLen == 0) {
        return sortkey.reset();
    }

    uint8_t *result;
    int32_t resultCapacity;
    if (sortkey.fCapacity >= (sourceLen * 3)) {

        result = sortkey.fBytes;
        resultCapacity = sortkey.fCapacity;
    } else {
        result = NULL;
        resultCapacity = 0;
    }
    int32_t resultLen = ucol_getSortKeyWithAllocation(ucollator, source, sourceLen,
                                                      result, resultCapacity, &status);

    if (U_SUCCESS(status)) {
        if (result == sortkey.fBytes) {
            sortkey.setLength(resultLen);
        } else {
            sortkey.adopt(result, resultCapacity, resultLen);
        }
    } else {
        if (result != sortkey.fBytes) {
            uprv_free(result);
        }
        sortkey.setToBogus();
    }
    return sortkey;
}
