subFind(const UnicodeString &text, int32_t start, int32_t types,
                       int32_t &matchLength, UErrorCode &status) const {
    matchLength = 0;
    if (U_FAILURE(status)) {
        return NULL;
    }
    if (fZoneStringsTrie.isEmpty()) {
        return NULL;
    }

    const ZoneStringInfo *result = NULL;
    const ZoneStringInfo *fallback = NULL;
    int32_t fallbackMatchLen = 0;

    ZoneStringSearchResultHandler handler(status);
    fZoneStringsTrie.search(text, start, (TextTrieMapSearchResultHandler*)&handler, status);
    if (U_SUCCESS(status)) {
        int32_t numMatches = handler.countMatches();
        for (int32_t i = 0; i < numMatches; i++) {
            int32_t tmpMatchLen = 0;
            const ZoneStringInfo *tmp = handler.getMatch(i, tmpMatchLen);
            if ((types & tmp->fType) != 0) {
                if (result == NULL || matchLength < tmpMatchLen) {
                    result = tmp;
                    matchLength = tmpMatchLen;
                } else if (matchLength == tmpMatchLen) {


                    if (tmp->isGeneric() && !result->isGeneric()) {
                        result = tmp;
                    }
                }
            } else if (result == NULL) {
                if (fallback == NULL || fallbackMatchLen < tmpMatchLen) {
                    fallback = tmp;
                    fallbackMatchLen = tmpMatchLen;
                } else if (fallbackMatchLen == tmpMatchLen) {
                    if (tmp->isGeneric() && !fallback->isGeneric()) {
                        fallback = tmp;
                    }
                }
            }
        }
        if (result == NULL && fallback != NULL) {
            result = fallback;
            matchLength = fallbackMatchLen;
        }
    }
    return result;
}
