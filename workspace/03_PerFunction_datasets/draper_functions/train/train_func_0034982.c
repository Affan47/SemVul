operator=(const TimeUnitFormat& other) {
    if (this == &other) {
        return *this;
    }
    MeasureFormat::operator=(other);
    for (TimeUnit::UTimeUnitFields i = TimeUnit::UTIMEUNIT_YEAR;
         i < TimeUnit::UTIMEUNIT_FIELD_COUNT;
         i = (TimeUnit::UTimeUnitFields)(i+1)) {
        deleteHash(fTimeUnitToCountToPatterns[i]);
        fTimeUnitToCountToPatterns[i] = NULL;
    }
    for (TimeUnit::UTimeUnitFields i = TimeUnit::UTIMEUNIT_YEAR;
         i < TimeUnit::UTIMEUNIT_FIELD_COUNT;
         i = (TimeUnit::UTimeUnitFields)(i+1)) {
        UErrorCode status = U_ZERO_ERROR;
        fTimeUnitToCountToPatterns[i] = initHash(status);
        if (U_SUCCESS(status)) {
            copyHash(other.fTimeUnitToCountToPatterns[i], fTimeUnitToCountToPatterns[i], status);
        } else {
            delete fTimeUnitToCountToPatterns[i];
            fTimeUnitToCountToPatterns[i] = NULL;
        }
    }
    fStyle = other.fStyle;
    return *this;
}
