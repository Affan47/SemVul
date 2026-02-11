findPrev(UDate base, UBool inclusive, UDate& transitionTime,
                            TimeZoneRule*& fromRule, TimeZoneRule*& toRule) const {
    if (fHistoricTransitions == NULL) {
        return FALSE;
    }
    UBool found = FALSE;
    Transition result;
    Transition *tzt = (Transition*)fHistoricTransitions->elementAt(0);
    UDate tt = tzt->time;
    if (inclusive && tt == base) {
        result = *tzt;
        found = TRUE;
    } else if (tt < base) {
        int32_t idx = fHistoricTransitions->size() - 1;
        tzt = (Transition*)fHistoricTransitions->elementAt(idx);
        tt = tzt->time;
        if (inclusive && tt == base) {
            result = *tzt;
            found = TRUE;
        } else if (tt < base) {
            if (fFinalRules != NULL) {

                TimeZoneRule *r0 = (TimeZoneRule*)fFinalRules->elementAt(0);
                TimeZoneRule *r1 = (TimeZoneRule*)fFinalRules->elementAt(1);
                UDate start0, start1;
                UBool avail0 = r0->getPreviousStart(base, r1->getRawOffset(), r1->getDSTSavings(), inclusive, start0);
                UBool avail1 = r1->getPreviousStart(base, r0->getRawOffset(), r0->getDSTSavings(), inclusive, start1);

                if (!avail0 && !avail1) {
                    return FALSE;
                }
                if (!avail1 || start0 > start1) {
                    result.time = start0;
                    result.from = r1;
                    result.to = r0;
                } else {
                    result.time = start1;
                    result.from = r0;
                    result.to = r1;
                }
            } else {
                result = *tzt;
            }
            found = TRUE;
        } else {

            idx--;
            while (idx >= 0) {
                tzt = (Transition*)fHistoricTransitions->elementAt(idx);
                tt = tzt->time;
                if (tt < base || (inclusive && tt == base)) {
                    break;
                }
                idx--;
            }
            result = *tzt;
            found = TRUE;
        }
    }
    if (found) {

        if (result.from->getRawOffset() == result.to->getRawOffset()
            && result.from->getDSTSavings() == result.to->getDSTSavings()) {

            return findPrev(result.time, FALSE ,
                transitionTime, fromRule, toRule);
        }
        transitionTime = result.time;
        fromRule = result.from;
        toRule = result.to;
        return TRUE;
    }
    return FALSE;
}
