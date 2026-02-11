compile(
                         const UnicodeString &pat,
                         UParseError &pp,
                         UErrorCode &e)
{
    fRXPat->fPatternString = new UnicodeString(pat);
    UText patternText = UTEXT_INITIALIZER;
    utext_openConstUnicodeString(&patternText, fRXPat->fPatternString, &e);

    if (U_SUCCESS(e)) {
        compile(&patternText, pp, e);
        utext_close(&patternText);
    }
}
