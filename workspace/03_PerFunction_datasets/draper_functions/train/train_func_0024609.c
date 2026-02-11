applyPattern(const UnicodeString& pattern,
                                     UErrorCode& status) {


    ParsePosition pos(0);
    applyPatternIgnoreSpace(pattern, pos, NULL, status);
    if (U_FAILURE(status)) return *this;

    int32_t i = pos.getIndex();

    ICU_Utility::skipWhitespace(pattern, i, TRUE);
    if (i != pattern.length()) {
        status = U_ILLEGAL_ARGUMENT_ERROR;
    }
    return *this;
}
