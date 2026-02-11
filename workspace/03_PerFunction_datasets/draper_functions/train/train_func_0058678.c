input() const {
    if (!fInput) {
        UErrorCode status = U_ZERO_ERROR;
        int32_t len16;
        if (UTEXT_USES_U16(fInputText)) {
            len16 = (int32_t)fInputLength;
        } else {
            len16 = utext_extract(fInputText, 0, fInputLength, NULL, 0, &status);
            status = U_ZERO_ERROR;
        }
        UnicodeString *result = new UnicodeString(len16, 0, 0);

        UChar *inputChars = result->getBuffer(len16);
        utext_extract(fInputText, 0, fInputLength, inputChars, len16, &status);
        result->releaseBuffer(len16);

        (*(const UnicodeString **)&fInput) = result;
    }

    return *fInput;
}
