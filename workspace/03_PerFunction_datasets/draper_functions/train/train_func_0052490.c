parsePragma(const UnicodeString& rule, int32_t pos, int32_t limit, UErrorCode& status) {
    int32_t array[2];


    pos += 4;


    int p = ICU_Utility::parsePattern(rule, pos, limit, UnicodeString(TRUE, PRAGMA_VARIABLE_RANGE, -1), array);
    if (p >= 0) {
        setVariableRange(array[0], array[1], status);
        return p;
    }

    p = ICU_Utility::parsePattern(rule, pos, limit, UnicodeString(TRUE, PRAGMA_MAXIMUM_BACKUP, -1), array);
    if (p >= 0) {
        pragmaMaximumBackup(array[0]);
        return p;
    }

    p = ICU_Utility::parsePattern(rule, pos, limit, UnicodeString(TRUE, PRAGMA_NFD_RULES, -1), NULL);
    if (p >= 0) {
        pragmaNormalizeRules(UNORM_NFD);
        return p;
    }

    p = ICU_Utility::parsePattern(rule, pos, limit, UnicodeString(TRUE, PRAGMA_NFC_RULES, -1), NULL);
    if (p >= 0) {
        pragmaNormalizeRules(UNORM_NFC);
        return p;
    }


    return -1;
}
