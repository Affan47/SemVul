parseSet(const UnicodeString& rule,
                                          ParsePosition& pos,
                                          UErrorCode& status) {
    UnicodeSet* set = new UnicodeSet(rule, pos, USET_IGNORE_SPACE, parseData, status);

    if (set == NULL) {
        status = U_MEMORY_ALLOCATION_ERROR;
        return (UChar)0x0000;
    }
    set->compact();
    return generateStandInFor(set, status);
}
