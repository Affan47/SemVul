getZoneIdByMetazone(const UnicodeString &mzid, const UnicodeString &region, UnicodeString &result) {
    UErrorCode status = U_ZERO_ERROR;
    const UChar *tzid = NULL;
    int32_t tzidLen = 0;
    char keyBuf[ZID_KEY_MAX + 1];
    int32_t keyLen = 0;

    if (mzid.length() >= ZID_KEY_MAX) {
        result.remove();
        return result;
    }

    keyLen = mzid.extract(0, mzid.length(), keyBuf, ZID_KEY_MAX, US_INV);

    UResourceBundle *rb = ures_openDirect(NULL, gMetaZones, &status);
    ures_getByKey(rb, gMapTimezonesTag, rb, &status);
    ures_getByKey(rb, keyBuf, rb, &status);

    if (U_SUCCESS(status)) {

        if (region.length() == 2 || region.length() == 3) {
            region.extract(0, region.length(), keyBuf, ZID_KEY_MAX, US_INV);
            tzid = ures_getStringByKey(rb, keyBuf, &tzidLen, &status);
            if (status == U_MISSING_RESOURCE_ERROR) {
                status = U_ZERO_ERROR;
            }
        }
        if (U_SUCCESS(status) && tzid == NULL) {

            tzid = ures_getStringByKey(rb, gWorldTag, &tzidLen, &status);
        }
    }
    ures_close(rb);

    if (tzid == NULL) {
        result.remove();
    } else {
        result.setTo(tzid, tzidLen);
    }

    return result;
}
