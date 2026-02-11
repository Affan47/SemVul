parseStarredCharacters(int32_t strength, int32_t i, UErrorCode &errorCode) {
    UnicodeString empty, raw;
    i = parseString(skipWhiteSpace(i), raw, errorCode);
    if(U_FAILURE(errorCode)) { return; }
    if(raw.isEmpty()) {
        setParseError("missing starred-relation string", errorCode);
        return;
    }
    UChar32 prev = -1;
    int32_t j = 0;
    for(;;) {
        while(j < raw.length()) {
            UChar32 c = raw.char32At(j);
            if(!nfd.isInert(c)) {
                setParseError("starred-relation string is not all NFD-inert", errorCode);
                return;
            }
            sink->addRelation(strength, empty, UnicodeString(c), empty, errorReason, errorCode);
            if(U_FAILURE(errorCode)) {
                setErrorContext();
                return;
            }
            j += U16_LENGTH(c);
            prev = c;
        }
        if(i >= rules->length() || rules->charAt(i) != 0x2d) {
            break;
        }
        if(prev < 0) {
            setParseError("range without start in starred-relation string", errorCode);
            return;
        }
        i = parseString(i + 1, raw, errorCode);
        if(U_FAILURE(errorCode)) { return; }
        if(raw.isEmpty()) {
            setParseError("range without end in starred-relation string", errorCode);
            return;
        }
        UChar32 c = raw.char32At(0);
        if(c < prev) {
            setParseError("range start greater than end in starred-relation string", errorCode);
            return;
        }

        UnicodeString s;
        while(++prev <= c) {
            if(!nfd.isInert(prev)) {
                setParseError("starred-relation string range is not all NFD-inert", errorCode);
                return;
            }
            if(U_IS_SURROGATE(prev)) {
                setParseError("starred-relation string range contains a surrogate", errorCode);
                return;
            }
            if(0xfffd <= prev && prev <= 0xffff) {
                setParseError("starred-relation string range contains U+FFFD, U+FFFE or U+FFFF", errorCode);
                return;
            }
            s.setTo(prev);
            sink->addRelation(strength, empty, s, empty, errorReason, errorCode);
            if(U_FAILURE(errorCode)) {
                setErrorContext();
                return;
            }
        }
        prev = -1;
        j = U16_LENGTH(c);
    }
    ruleIndex = skipWhiteSpace(i);
}
