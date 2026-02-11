initZoneStringFormat(void) {
    if (fZoneStringFormat == NULL) {
        UErrorCode status = U_ZERO_ERROR;
        if (fZoneStrings) {

            fZSFLocal = new ZoneStringFormat(fZoneStrings, fZoneStringsRowCount,
                fZoneStringsColCount, status);
            if (U_FAILURE(status)) {
                delete fZSFLocal;
            } else {
                fZoneStringFormat = (const ZoneStringFormat*)fZSFLocal;
            }
        } else {
            fZSFCachePtr = ZoneStringFormat::getZoneStringFormat(fZSFLocale, status);
            if (U_FAILURE(status)) {
                delete fZSFCachePtr;
            } else {
                fZoneStringFormat = fZSFCachePtr->get();
            }
        }
    }
}
