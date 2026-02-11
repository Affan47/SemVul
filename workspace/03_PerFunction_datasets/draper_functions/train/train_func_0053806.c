getTimeZoneGenericNames(UErrorCode& status) const {
    if (U_FAILURE(status)) {
        return NULL;
    }

    UBool create;
    UMTX_CHECK(&gZoneMetaLock, (fTimeZoneGenericNames == NULL), create);
    if (create) {
        TimeZoneFormatImpl *nonConstThis = const_cast<TimeZoneFormatImpl *>(this);
        umtx_lock(&nonConstThis->fLock);
        {
            if (fTimeZoneGenericNames == NULL) {
                nonConstThis->fTimeZoneGenericNames = new TimeZoneGenericNames(fLocale, status);
                if (U_SUCCESS(status) && fTimeZoneGenericNames == NULL) {
                    status = U_MEMORY_ALLOCATION_ERROR;
                }
            }
        }
        umtx_unlock(&nonConstThis->fLock);
    }

    return fTimeZoneGenericNames;
}
