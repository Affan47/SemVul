dispose()
{
    if (ruleSets) {
        for (NFRuleSet** p = ruleSets; *p; ++p) {
            delete *p;
        }
        uprv_free(ruleSets);
        ruleSets = NULL;
    }

    if (ruleSetDescriptions) {
        delete [] ruleSetDescriptions;
    }

#if !UCONFIG_NO_COLLATION
    delete collator;
#endif
    collator = NULL;

    delete decimalFormatSymbols;
    decimalFormatSymbols = NULL;

    delete lenientParseRules;
    lenientParseRules = NULL;

    if (localizations) localizations = localizations->unref();
}
