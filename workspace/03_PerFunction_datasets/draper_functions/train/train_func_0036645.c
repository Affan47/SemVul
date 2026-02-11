operator=(const RuleBasedNumberFormat& rhs)
{
    if (this == &rhs) {
        return *this;
    }
    NumberFormat::operator=(rhs);
    UErrorCode status = U_ZERO_ERROR;
    dispose();
    locale = rhs.locale;
    lenient = rhs.lenient;

    UParseError perror;
    init(rhs.originalDescription, rhs.localizations ? rhs.localizations->ref() : NULL, perror, status);
    setDecimalFormatSymbols(*rhs.getDecimalFormatSymbols());
    setDefaultRuleSet(rhs.getDefaultRuleSetName(), status);

    capitalizationInfoSet = rhs.capitalizationInfoSet;
    capitalizationForUIListMenu = rhs.capitalizationForUIListMenu;
    capitalizationForStandAlone = rhs.capitalizationForStandAlone;
#if !UCONFIG_NO_BREAK_ITERATION
    capitalizationBrkIter = (rhs.capitalizationBrkIter!=NULL)? rhs.capitalizationBrkIter->clone(): NULL;
#endif

    return *this;
}
