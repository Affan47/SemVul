loadStrings(const UnicodeString& tzCanonicalID) {

    getGenericLocationName(tzCanonicalID);


    UErrorCode status = U_ZERO_ERROR;

    const UnicodeString *mzID;
    UnicodeString goldenID;
    UnicodeString mzGenName;
    UTimeZoneNameType genNonLocTypes[] = {
        UTZNM_LONG_GENERIC, UTZNM_SHORT_GENERIC,
        UTZNM_UNKNOWN
    };

    StringEnumeration *mzIDs = fTimeZoneNames->getAvailableMetaZoneIDs(tzCanonicalID, status);
    while ((mzID = mzIDs->snext(status))) {
        if (U_FAILURE(status)) {
            break;
        }


        fTimeZoneNames->getReferenceZoneID(*mzID, fTargetRegion, goldenID);
        if (tzCanonicalID != goldenID) {
            for (int32_t i = 0; genNonLocTypes[i] != UTZNM_UNKNOWN; i++) {
                fTimeZoneNames->getMetaZoneDisplayName(*mzID, genNonLocTypes[i], mzGenName);
                if (!mzGenName.isEmpty()) {

                    getPartialLocationName(tzCanonicalID, *mzID,
                        (genNonLocTypes[i] == UTZNM_LONG_GENERIC), mzGenName);
                }
            }
        }
    }
    if (mzIDs != NULL) {
        delete mzIDs;
    }
}
