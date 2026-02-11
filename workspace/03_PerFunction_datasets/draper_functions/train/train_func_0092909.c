getTimeZoneRules(const InitialTimeZoneRule*& initial,
                                const TimeZoneRule* trsrules[],
                                int32_t& trscount,
                                UErrorCode& status) const {
    if (U_FAILURE(status)) {
        return;
    }
    checkTransitionRules(status);
    if (U_FAILURE(status)) {
        return;
    }


    initial = initialRule;


    int32_t cnt = 0;
    if (historicRules != NULL && trscount > cnt) {


        for (int32_t i = 0; i < historicRuleCount; i++) {
            if (historicRules[i] != NULL) {
                trsrules[cnt++] = historicRules[i];
                if (cnt >= trscount) {
                    break;
                }
            }
        }
    }
    if (finalZoneWithStartYear != NULL && trscount > cnt) {
        const InitialTimeZoneRule *tmpini;
        int32_t tmpcnt = trscount - cnt;
        finalZoneWithStartYear->getTimeZoneRules(tmpini, &trsrules[cnt], tmpcnt, status);
        if (U_FAILURE(status)) {
            return;
        }
        cnt += tmpcnt;
    }

    trscount = cnt;
}
