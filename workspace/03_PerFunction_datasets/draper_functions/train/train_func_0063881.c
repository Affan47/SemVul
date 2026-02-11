getZoneByName(const UResourceBundle* top, const UnicodeString& id, UResourceBundle *oldbundle, UErrorCode& status) {

    UResourceBundle *tmp = ures_getByKey(top, kNAMES, NULL, &status);


    int32_t idx = findInStringArray(tmp, id, status);

    if((idx == -1) && U_SUCCESS(status)) {

        status = U_MISSING_RESOURCE_ERROR;


    } else {
        U_DEBUG_TZ_MSG(("gzbn: oldbundle= size %d, type %d, %s\n", ures_getSize(tmp), ures_getType(tmp), u_errorName(status)));
        tmp = ures_getByKey(top, kZONES, tmp, &status);
        U_DEBUG_TZ_MSG(("gzbn: loaded ZONES, size %d, type %d, path %s %s\n", ures_getSize(tmp), ures_getType(tmp), ures_getPath(tmp), u_errorName(status)));
        oldbundle = ures_getByIndex(tmp, idx, oldbundle, &status);
        U_DEBUG_TZ_MSG(("gzbn: loaded z#%d, size %d, type %d, path %s, %s\n", idx, ures_getSize(oldbundle), ures_getType(oldbundle), ures_getPath(oldbundle),  u_errorName(status)));
    }
    ures_close(tmp);
    if(U_FAILURE(status)) {

        return NULL;
    } else {
        return oldbundle;
    }
}
