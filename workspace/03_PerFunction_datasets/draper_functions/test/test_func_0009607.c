operator=(const OlsonTimeZone& other) {
    transitionCount = other.transitionCount;
    typeCount = other.typeCount;
    transitionTimes = other.transitionTimes;
    typeOffsets = other.typeOffsets;
    typeData = other.typeData;
    finalYear = other.finalYear;
    finalMillis = other.finalMillis;
    delete finalZone;
    finalZone = (other.finalZone != 0) ?
        (SimpleTimeZone*) other.finalZone->clone() : 0;
    clearTransitionRules();
    return *this;
}
