setupCurrencyAffixPatterns(UErrorCode& status) {
    if (U_FAILURE(status)) {
        return;
    }
    UParseError parseErr;
    fAffixPatternsForCurrency = initHashForAffixPattern(status);
    if (U_FAILURE(status)) {
        return;
    }

    NumberingSystem *ns = NumberingSystem::createInstance(fSymbols->getLocale(),status);
    if (U_FAILURE(status)) {
        return;
    }


    UnicodeString currencyPattern;
    UErrorCode error = U_ZERO_ERROR;

    UResourceBundle *resource = ures_open(NULL, fSymbols->getLocale().getName(), &error);
    UResourceBundle *numElements = ures_getByKeyWithFallback(resource, fgNumberElements, NULL, &error);
    resource = ures_getByKeyWithFallback(numElements, ns->getName(), resource, &error);
    resource = ures_getByKeyWithFallback(resource, fgPatterns, resource, &error);
    int32_t patLen = 0;
    const UChar *patResStr = ures_getStringByKeyWithFallback(resource, fgCurrencyFormat,  &patLen, &error);
    if ( error == U_MISSING_RESOURCE_ERROR && uprv_strcmp(ns->getName(),fgLatn)) {
        error = U_ZERO_ERROR;
        resource = ures_getByKeyWithFallback(numElements, fgLatn, resource, &error);
        resource = ures_getByKeyWithFallback(resource, fgPatterns, resource, &error);
        patResStr = ures_getStringByKeyWithFallback(resource, fgCurrencyFormat,  &patLen, &error);
    }
    ures_close(numElements);
    ures_close(resource);
    delete ns;

    if (U_SUCCESS(error)) {
        applyPatternWithoutExpandAffix(UnicodeString(patResStr, patLen), false,
                                       parseErr, status);
        AffixPatternsForCurrency* affixPtn = new AffixPatternsForCurrency(
                                                    *fNegPrefixPattern,
                                                    *fNegSuffixPattern,
                                                    *fPosPrefixPattern,
                                                    *fPosSuffixPattern,
                                                    UCURR_SYMBOL_NAME);
        fAffixPatternsForCurrency->put(UNICODE_STRING("default", 7), affixPtn, status);
    }


    Hashtable* pluralPtn = fCurrencyPluralInfo->fPluralCountToCurrencyUnitPattern;
    const UHashElement* element = NULL;
    int32_t pos = -1;
    Hashtable pluralPatternSet;
    while ((element = pluralPtn->nextElement(pos)) != NULL) {
        const UHashTok valueTok = element->value;
        const UnicodeString* value = (UnicodeString*)valueTok.pointer;
        const UHashTok keyTok = element->key;
        const UnicodeString* key = (UnicodeString*)keyTok.pointer;
        if (pluralPatternSet.geti(*value) != 1) {
            pluralPatternSet.puti(*value, 1, status);
            applyPatternWithoutExpandAffix(*value, false, parseErr, status);
            AffixPatternsForCurrency* affixPtn = new AffixPatternsForCurrency(
                                                    *fNegPrefixPattern,
                                                    *fNegSuffixPattern,
                                                    *fPosPrefixPattern,
                                                    *fPosSuffixPattern,
                                                    UCURR_LONG_NAME);
            fAffixPatternsForCurrency->put(*key, affixPtn, status);
        }
    }
}
