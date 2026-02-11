applyPattern(const UnicodeString& pattern,
                              ParsePosition& pos,
                              uint32_t options,
                              const SymbolTable* symbols,
                              UErrorCode& status) {
    if (U_FAILURE(status) || isFrozen()) {
        return *this;
    }


    UnicodeString rebuiltPat;
    RuleCharacterIterator chars(pattern, symbols, pos);
    applyPattern(chars, symbols, rebuiltPat, options, status);
    if (U_FAILURE(status)) return *this;
    if (chars.inVariable()) {

        status = U_MALFORMED_SET;
        return *this;
    }
    setPattern(rebuiltPat);
    return *this;
}
