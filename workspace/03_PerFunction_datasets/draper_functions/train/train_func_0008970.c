getCurrencyPluralPattern(const UnicodeString&  pluralCount,
                                             UnicodeString& result) const {
    const UnicodeString* currencyPluralPattern =
        (UnicodeString*)fPluralCountToCurrencyUnitPattern->get(pluralCount);
    if (currencyPluralPattern == NULL) {

        if (pluralCount.compare(gPluralCountOther, 5)) {
            currencyPluralPattern =
                (UnicodeString*)fPluralCountToCurrencyUnitPattern->get(UnicodeString(TRUE, gPluralCountOther, 5));
        }
        if (currencyPluralPattern == NULL) {


            result = UnicodeString(gDefaultCurrencyPluralPattern);
            return result;
        }
    }
    result = *currencyPluralPattern;
    return result;
}
