getRules(
        const char *localeID, const char *collationType,
        const char *& , UErrorCode &errorCode) {
    delete rules;
    return rules = CollationLoader::loadRules(localeID, collationType, errorCode);
}
