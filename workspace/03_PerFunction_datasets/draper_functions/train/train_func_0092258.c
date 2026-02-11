getZoneStringFormat(const Locale& locale, UErrorCode &status) {
    umtx_lock(&gZSFCacheLock);
    if (gZoneStringFormatCache == NULL) {
        gZoneStringFormatCache = new ZSFCache(10 );
        ucln_i18n_registerCleanup(UCLN_I18N_ZSFORMAT, zoneStringFormat_cleanup);
    }
    umtx_unlock(&gZSFCacheLock);

    return gZoneStringFormatCache->get(locale, status);
}
