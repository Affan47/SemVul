matches(UErrorCode& status) {
    if (U_FAILURE(status)) {
        return NULL;
    }
    if (fMatches != NULL) {
        return fMatches;
    }
    fMatches = new UVector(deleteMatchInfo, NULL, status);
    if (fMatches == NULL) {
        status = U_MEMORY_ALLOCATION_ERROR;
    } else if (U_FAILURE(status)) {
        delete fMatches;
        fMatches = NULL;
    }
    return fMatches;
}
