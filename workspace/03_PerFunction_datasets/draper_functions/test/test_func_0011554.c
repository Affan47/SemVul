operator=(const OlsonTimeZone& other) {
    canonicalID = other.canonicalID;

    transitionTimesPre32 = other.transitionTimesPre32;
    transitionTimes32 = other.transitionTimes32;
    transitionTimesPost32 = other.transitionTimesPost32;

    transitionCountPre32 = other.transitionCountPre32;
    transitionCount32 = other.transitionCount32;
    transitionCountPost32 = other.transitionCountPost32;

    typeCount = other.typeCount;
    typeOffsets = other.typeOffsets;
    typeMapData = other.typeMapData;

    delete finalZone;
    finalZone = (other.finalZone != 0) ?
        (SimpleTimeZone*) other.finalZone->clone() : 0;

    finalStartYear = other.finalStartYear;
    finalStartMillis = other.finalStartMillis;

    clearTransitionRules();

    return *this;
}
