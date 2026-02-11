initDangiCalZoneAstroCalc(void) {
    U_ASSERT(gDangiCalendarZoneAstroCalc == NULL);
    const UDate millis1897[] = { (UDate)((1897 - 1970) * 365 * kOneDay) };
    const UDate millis1898[] = { (UDate)((1898 - 1970) * 365 * kOneDay) };
    const UDate millis1912[] = { (UDate)((1912 - 1970) * 365 * kOneDay) };
    InitialTimeZoneRule* initialTimeZone = new InitialTimeZoneRule(UNICODE_STRING_SIMPLE("GMT+8"), 8*kOneHour, 0);
    TimeZoneRule* rule1897 = new TimeArrayTimeZoneRule(UNICODE_STRING_SIMPLE("Korean 1897"), 7*kOneHour, 0, millis1897, 1, DateTimeRule::STANDARD_TIME);
    TimeZoneRule* rule1898to1911 = new TimeArrayTimeZoneRule(UNICODE_STRING_SIMPLE("Korean 1898-1911"), 8*kOneHour, 0, millis1898, 1, DateTimeRule::STANDARD_TIME);
    TimeZoneRule* ruleFrom1912 = new TimeArrayTimeZoneRule(UNICODE_STRING_SIMPLE("Korean 1912-"), 9*kOneHour, 0, millis1912, 1, DateTimeRule::STANDARD_TIME);
    UErrorCode status = U_ZERO_ERROR;
    RuleBasedTimeZone* dangiCalZoneAstroCalc = new RuleBasedTimeZone(UNICODE_STRING_SIMPLE("KOREA_ZONE"), initialTimeZone);
    dangiCalZoneAstroCalc->addTransitionRule(rule1897, status);
    dangiCalZoneAstroCalc->addTransitionRule(rule1898to1911, status);
    dangiCalZoneAstroCalc->addTransitionRule(ruleFrom1912, status);
    dangiCalZoneAstroCalc->complete(status);
    if (U_SUCCESS(status)) {
        gDangiCalendarZoneAstroCalc = dangiCalZoneAstroCalc;
    } else {
        delete dangiCalZoneAstroCalc;
        gDangiCalendarZoneAstroCalc = NULL;
    }
    ucln_i18n_registerCleanup(UCLN_I18N_DANGI_CALENDAR, calendar_dangi_cleanup);
}
