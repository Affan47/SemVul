loadNumericDateFormatterPattern(
        const UResourceBundle *resource,
        const char *pattern,
        UErrorCode &status) {
    UnicodeString result;
    if (U_FAILURE(status)) {
        return result;
    }
    CharString chs;
    chs.append("durationUnits", status)
            .append("/", status).append(pattern, status);
    LocalUResourceBundlePointer patternBundle(
            ures_getByKeyWithFallback(
                resource,
                chs.data(),
                NULL,
                &status));
    if (U_FAILURE(status)) {
        return result;
    }
    getString(patternBundle.getAlias(), result, status);

    int32_t len = result.length();
    UChar *buffer = result.getBuffer(len);
    for (int32_t i = 0; i < len; ++i) {
        if (buffer[i] == 0x68) {
            buffer[i] = 0x48;
        }
    }
    result.releaseBuffer(len);
    return result;
}
