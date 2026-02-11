createRules(const UnicodeString& description, UErrorCode& status) {
    if (U_FAILURE(status)) {
        return NULL;
    }

    PluralRuleParser parser;
    PluralRules *newRules = new PluralRules(status);
    if (U_SUCCESS(status) && newRules == NULL) {
        status = U_MEMORY_ALLOCATION_ERROR;
    }
    parser.parse(description, newRules, status);
    if (U_FAILURE(status)) {
        delete newRules;
        newRules = NULL;
    }
    return newRules;
}
