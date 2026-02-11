_normalize(const Normalizer2 *n2, const UChar *s, int32_t length,
                UnicodeString &normalized, UErrorCode *pErrorCode) {
    UnicodeString str(length<0, s, length);


    int32_t spanQCYes=n2->spanQuickCheckYes(str, *pErrorCode);
    if (U_FAILURE(*pErrorCode)) {
        return FALSE;
    }


    if(spanQCYes<str.length()) {
        UnicodeString unnormalized=str.tempSubString(spanQCYes);
        normalized.setTo(FALSE, str.getBuffer(), spanQCYes);
        n2->normalizeSecondAndAppend(normalized, unnormalized, *pErrorCode);
        if (U_SUCCESS(*pErrorCode)) {
            return TRUE;
        }
    }
    return FALSE;
}
