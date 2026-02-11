initializeCalendar(TimeZone* adoptZone, const Locale& locale, UErrorCode& status)
{
    if(!U_FAILURE(status)) {
        fCalendar = Calendar::createInstance(adoptZone?adoptZone:TimeZone::createDefault(), locale, status);
    }
    if (U_SUCCESS(status) && fCalendar == NULL) {
        status = U_MEMORY_ALLOCATION_ERROR;
    }
    return fCalendar;
}
