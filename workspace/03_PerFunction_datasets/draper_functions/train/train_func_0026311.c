setTimeInMillis( double millis, UErrorCode& status ) {
    if(U_FAILURE(status))
        return;

    if (millis > MAX_MILLIS) {
        millis = MAX_MILLIS;
    } else if (millis < MIN_MILLIS) {
        millis = MIN_MILLIS;
    }

    fTime = millis;
    fAreFieldsSet = fAreAllFieldsSet = FALSE;
    fIsTimeSet = fAreFieldsVirtuallySet = TRUE;

    for (int32_t i=0; i<UCAL_FIELD_COUNT; ++i) {
        fFields[i]     = 0;
        fStamp[i]     = kUnset;
        fIsSet[i]     = FALSE;
    }


}
