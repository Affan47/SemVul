isMatchAtCPBoundary(const UChar *start, const UChar *match, const UChar *matchLimit, const UChar *limit) {
    if(U16_IS_TRAIL(*match) && start!=match && U16_IS_LEAD(*(match-1))) {

        return FALSE;
    }
    if(U16_IS_LEAD(*(matchLimit-1)) && match!=limit && U16_IS_TRAIL(*matchLimit)) {

        return FALSE;
    }
    return TRUE;
}
