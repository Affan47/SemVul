createVTimeZoneByID(const UnicodeString& ID) {
    VTimeZone *vtz = new VTimeZone();
    vtz->tz = (BasicTimeZone*)TimeZone::createTimeZone(ID);
    vtz->tz->getID(vtz->olsonzid);


    UErrorCode status = U_ZERO_ERROR;
    UResourceBundle *bundle = NULL;
    const UChar* versionStr = NULL;
    int32_t len;
    bundle = ures_openDirect(NULL, "zoneinfo", &status);
    versionStr = ures_getStringByKey(bundle, "TZVersion", &len, &status);
    if (U_SUCCESS(status)) {
        vtz->icutzver.setTo(versionStr, len);
    }
    ures_close(bundle);
    return vtz;
}
