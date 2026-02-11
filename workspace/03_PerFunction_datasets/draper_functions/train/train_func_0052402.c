operator=(const Calendar &right)
{
    if (this != &right) {
        uprv_arrayCopy(right.fFields, fFields, UCAL_FIELD_COUNT);
        uprv_arrayCopy(right.fIsSet, fIsSet, UCAL_FIELD_COUNT);
        uprv_arrayCopy(right.fStamp, fStamp, UCAL_FIELD_COUNT);
        fTime                    = right.fTime;
        fIsTimeSet               = right.fIsTimeSet;
        fAreAllFieldsSet         = right.fAreAllFieldsSet;
        fAreFieldsSet            = right.fAreFieldsSet;
        fAreFieldsVirtuallySet   = right.fAreFieldsVirtuallySet;
        fLenient                 = right.fLenient;
        fRepeatedWallTime        = right.fRepeatedWallTime;
        fSkippedWallTime         = right.fSkippedWallTime;
        if (fZone != NULL) {
            delete fZone;
        }
        if (right.fZone != NULL) {
            fZone                = right.fZone->clone();
        }
        fFirstDayOfWeek          = right.fFirstDayOfWeek;
        fMinimalDaysInFirstWeek  = right.fMinimalDaysInFirstWeek;
        fWeekendOnset            = right.fWeekendOnset;
        fWeekendOnsetMillis      = right.fWeekendOnsetMillis;
        fWeekendCease            = right.fWeekendCease;
        fWeekendCeaseMillis      = right.fWeekendCeaseMillis;
        fNextStamp               = right.fNextStamp;
        uprv_strcpy(validLocale, right.validLocale);
        uprv_strcpy(actualLocale, right.actualLocale);
    }

    return *this;
}
