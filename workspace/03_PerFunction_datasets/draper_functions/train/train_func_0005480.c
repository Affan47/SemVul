_createTimeZone(const UChar* zoneID, int32_t len, UErrorCode* ec) {
    TimeZone* zone = NULL;
    if (ec!=NULL && U_SUCCESS(*ec)) {


        int32_t l = (len<0 ? u_strlen(zoneID) : len);
        UnicodeString zoneStrID;
        zoneStrID.setTo((UBool)(len < 0), zoneID, l);
        zone = TimeZone::createTimeZone(zoneStrID);
        if (zone == NULL) {
            *ec = U_MEMORY_ALLOCATION_ERROR;
        }
    }
    return zone;
}
