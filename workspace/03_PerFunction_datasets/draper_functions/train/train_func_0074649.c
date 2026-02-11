getOffsetInternal(UDate date, UBool local,
                                     int32_t NonExistingTimeOpt, int32_t DuplicatedTimeOpt,
                                     int32_t& rawOffset, int32_t& dstOffset,
                                     UErrorCode& status) const {
    rawOffset = 0;
    dstOffset = 0;

    if (U_FAILURE(status)) {
        return;
    }
    if (!fUpToDate) {


        status = U_INVALID_STATE_ERROR;
        return;
    }
    const TimeZoneRule *rule = NULL;
    if (fHistoricTransitions == NULL) {
        rule = fInitialRule;
    } else {
        UDate tstart = getTransitionTime((Transition*)fHistoricTransitions->elementAt(0),
            local, NonExistingTimeOpt, DuplicatedTimeOpt);
        if (date < tstart) {
            rule = fInitialRule;
        } else {
            int32_t idx = fHistoricTransitions->size() - 1;
            UDate tend = getTransitionTime((Transition*)fHistoricTransitions->elementAt(idx),
                local, NonExistingTimeOpt, DuplicatedTimeOpt);
            if (date > tend) {
                if (fFinalRules != NULL) {
                    rule = findRuleInFinal(date, local, NonExistingTimeOpt, DuplicatedTimeOpt);
                } else {

                    rule = ((Transition*)fHistoricTransitions->elementAt(idx))->to;
                }
            } else {

                while (idx >= 0) {
                    if (date >= getTransitionTime((Transition*)fHistoricTransitions->elementAt(idx),
                        local, NonExistingTimeOpt, DuplicatedTimeOpt)) {
                        break;
                    }
                    idx--;
                }
                rule = ((Transition*)fHistoricTransitions->elementAt(idx))->to;
            }
        }
    }
    if (rule != NULL) {
        rawOffset = rule->getRawOffset();
        dstOffset = rule->getDSTSavings();
    }
}
