closeOverComposites(UErrorCode &errorCode) {
    UnicodeSet composites(UNICODE_STRING_SIMPLE("[:NFD_QC=N:]"), errorCode);
    if(U_FAILURE(errorCode)) { return; }

    composites.remove(Hangul::HANGUL_BASE, Hangul::HANGUL_END);
    UnicodeString prefix;
    UnicodeString nfdString;
    UnicodeSetIterator iter(composites);
    while(iter.next()) {
        U_ASSERT(!iter.isString());
        nfd.getDecomposition(iter.getCodepoint(), nfdString);
        cesLength = dataBuilder->getCEs(nfdString, ces, 0);
        if(cesLength > Collation::MAX_EXPANSION_LENGTH) {


            continue;
        }
        const UnicodeString &composite(iter.getString());
        addIfDifferent(prefix, composite, ces, cesLength, Collation::UNASSIGNED_CE32, errorCode);
    }
}
