skipWhitespace(const UnicodeString& str, int32_t& pos,
                                    UBool advance) {
    int32_t p = pos;
    const UChar* s = str.getBuffer();
    p = (int32_t)(PatternProps::skipWhiteSpace(s + p, str.length() - p) - s);
    if (advance) {
        pos = p;
    }
    return p;
}
