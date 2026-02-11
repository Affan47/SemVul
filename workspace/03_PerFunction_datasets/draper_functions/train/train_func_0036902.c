adopt(const UChar * s, UErrorCode &status) {
    const UChar *pooledString;
    if (U_FAILURE(status)) {
        return &EmptyString;
    }
    if (s != NULL) {
        pooledString = static_cast<UChar *>(uhash_get(fHash, s));
        if (pooledString == NULL) {
            UChar *ncs = const_cast<UChar *>(s);
            uhash_put(fHash, ncs, ncs, &status);
        }
    }
    return s;
}
