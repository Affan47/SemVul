hasSameRules(const TimeZone& other) const {
    if (this == &other) {
        return TRUE;
    }
    if (typeid(*this) != typeid(other)) {
        return FALSE;
    }
    const RuleBasedTimeZone& that = (const RuleBasedTimeZone&)other;
    if (*fInitialRule != *(that.fInitialRule)) {
        return FALSE;
    }
    if (compareRules(fHistoricRules, that.fHistoricRules)
        && compareRules(fFinalRules, that.fFinalRules)) {
        return TRUE;
    }
    return FALSE;
}
