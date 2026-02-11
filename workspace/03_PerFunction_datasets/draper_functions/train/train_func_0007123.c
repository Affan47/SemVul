parseRelationStrings(int32_t strength, int32_t i, UErrorCode &errorCode) {


    UnicodeString prefix, str, extension;
    i = parseTailoringString(i, str, errorCode);
    if(U_FAILURE(errorCode)) { return; }
    UChar next = (i < rules->length()) ? rules->charAt(i) : 0;
    if(next == 0x7c) {
        prefix = str;
        i = parseTailoringString(i + 1, str, errorCode);
        if(U_FAILURE(errorCode)) { return; }
        next = (i < rules->length()) ? rules->charAt(i) : 0;
    }
    if(next == 0x2f) {
        i = parseTailoringString(i + 1, extension, errorCode);
    }
    if(!prefix.isEmpty()) {
        UChar32 prefix0 = prefix.char32At(0);
        UChar32 c = str.char32At(0);
        if(!nfc.hasBoundaryBefore(prefix0) || !nfc.hasBoundaryBefore(c)) {
            setParseError("in 'prefix|str', prefix and str must each start with an NFC boundary",
                          errorCode);
            return;
        }
    }
    sink->addRelation(strength, prefix, str, extension, errorReason, errorCode);
    if(U_FAILURE(errorCode)) { setErrorContext(); }
    ruleIndex = i;
}
