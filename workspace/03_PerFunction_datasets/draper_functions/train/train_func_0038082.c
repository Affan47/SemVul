initTZDataVersion(UErrorCode &status) {
    ucln_i18n_registerCleanup(UCLN_I18N_TIMEZONE, timeZone_cleanup);
    int32_t len = 0;
    UResourceBundle *bundle = ures_openDirect(NULL, kZONEINFO, &status);
    const UChar *tzver = ures_getStringByKey(bundle, kTZVERSION, &len, &status);

    if (U_SUCCESS(status)) {
        if (len >= (int32_t)sizeof(TZDATA_VERSION)) {

            len = sizeof(TZDATA_VERSION) - 1;
        }
        u_UCharsToChars(tzver, TZDATA_VERSION, len);
    }
    ures_close(bundle);

}
