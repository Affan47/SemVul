getReferenceZoneID(const UnicodeString& mzID, const char* region, UnicodeString& tzID) const {
    ZoneMeta::getZoneIdByMetazone(mzID, UnicodeString(region, -1, US_INV), tzID);
    return tzID;
}
