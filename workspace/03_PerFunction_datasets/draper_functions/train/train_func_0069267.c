createZoneStringsArray(UDate date, int32_t &rowCount, int32_t &colCount, UErrorCode &status) const {
    if (U_FAILURE(status)) {
        return NULL;
    }
    UnicodeString **result = NULL;
    rowCount = 0;
    colCount = 0;


    UVector canonicalIDs(uhash_deleteUnicodeString, uhash_compareUnicodeString, status);
    if (U_FAILURE(status)) {
        return NULL;
    }
    StringEnumeration *tzids = TimeZone::createEnumeration();
    const UChar *tzid;
    while ((tzid = tzids->unext(NULL, status))) {
        if (U_FAILURE(status)) {
            delete tzids;
            return NULL;
        }
        UnicodeString utzid(tzid);
        UnicodeString canonicalID;
        TimeZone::getCanonicalID(UnicodeString(tzid), canonicalID, status);
        if (U_FAILURE(status)) {

            status = U_ZERO_ERROR;
            continue;
        }
        if (utzid == canonicalID) {
            canonicalIDs.addElement(new UnicodeString(utzid), status);
            if (U_FAILURE(status)) {
                delete tzids;
                return NULL;
            }
        }
    }
    delete tzids;


    result = (UnicodeString**)uprv_malloc(canonicalIDs.size() * sizeof(UnicodeString*));
    if (result == NULL) {
        status = U_MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    for (int32_t i = 0; i < canonicalIDs.size(); i++) {
        result[i] = new UnicodeString[8];
        UnicodeString *id = (UnicodeString*)canonicalIDs.elementAt(i);
        result[i][0].setTo(*id);
        getLongStandard(*id, date, result[i][1]);
        getShortStandard(*id, date, FALSE, result[i][2]);
        getLongDaylight(*id, date, result[i][3]);
        getShortDaylight(*id, date, FALSE, result[i][4]);
        getGenericLocation(*id, result[i][5]);
        getLongGenericNonLocation(*id, date, result[i][6]);
        getShortGenericNonLocation(*id, date, FALSE, result[i][7]);
    }

    rowCount = canonicalIDs.size();
    colCount = 8;
    return result;
}
