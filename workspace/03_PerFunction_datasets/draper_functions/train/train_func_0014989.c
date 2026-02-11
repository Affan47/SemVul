initChineseCalZoneAstroCalc() {
    gChineseCalendarZoneAstroCalc = new SimpleTimeZone(CHINA_OFFSET, UNICODE_STRING_SIMPLE("CHINA_ZONE") );
    ucln_i18n_registerCleanup(UCLN_I18N_CHINESE_CALENDAR, calendar_chinese_cleanup);
}
