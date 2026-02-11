formatExemplarLocation(const TimeZone& tz, UnicodeString& name) const {
    UnicodeString location;
    const UChar* canonicalID = ZoneMeta::getCanonicalCLDRID(tz);

    if (canonicalID) {
        fTimeZoneNames->getExemplarLocationName(UnicodeString(canonicalID), location);
    }
    if (location.length() > 0) {
        name.setTo(location);
    } else {

        fTimeZoneNames->getExemplarLocationName(UnicodeString(UNKNOWN_ZONE_ID), location);
        if (location.length() > 0) {
            name.setTo(location);
        } else {

            name.setTo(UNKNOWN_LOCATION, -1);
        }
    }
    return name;
}
