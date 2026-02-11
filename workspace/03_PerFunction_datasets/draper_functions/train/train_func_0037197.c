operator=(const PluralFormat& other) {
    if (this != &other) {
        UErrorCode status = U_ZERO_ERROR;
        delete pluralRules;
        delete fParsedValuesHash;
        delete numberFormat;
        locale = other.locale;
        pluralRules = other.pluralRules->clone();
        pattern = other.pattern;
        copyHashtable(other.fParsedValuesHash, status);
        if (U_FAILURE(status)) {
            delete pluralRules;
            pluralRules = NULL;
            fParsedValuesHash = NULL;
            numberFormat = NULL;
            return *this;
        }
        numberFormat=NumberFormat::createInstance(locale, status);
        if (U_FAILURE(status)) {
            delete pluralRules;
            delete fParsedValuesHash;
            pluralRules = NULL;
            fParsedValuesHash = NULL;
            numberFormat = NULL;
            return *this;
        }
        replacedNumberFormat=other.replacedNumberFormat;
    }

    return *this;
}
