snext(UErrorCode& status) {
    if (U_SUCCESS(status) && fMetaZoneIDs != NULL && fPos < fLen) {
        unistr.setTo((const UChar*)fMetaZoneIDs->elementAt(fPos++), -1);
        return &unistr;
    }
    return NULL;
}
