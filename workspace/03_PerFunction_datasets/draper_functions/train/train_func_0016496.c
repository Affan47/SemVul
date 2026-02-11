getDisplayCountry(const Locale &displayLocale,
                          UnicodeString &result) const {
    UChar *buffer;
    UErrorCode errorCode=U_ZERO_ERROR;
    int32_t length;

    buffer=result.getBuffer(ULOC_FULLNAME_CAPACITY);
    if(buffer==0) {
        result.truncate(0);
        return result;
    }

    length=uloc_getDisplayCountry(fullName, displayLocale.fullName,
                                  buffer, result.getCapacity(),
                                  &errorCode);
    result.releaseBuffer(U_SUCCESS(errorCode) ? length : 0);

    if(errorCode==U_BUFFER_OVERFLOW_ERROR) {
        buffer=result.getBuffer(length);
        if(buffer==0) {
            result.truncate(0);
            return result;
        }
        errorCode=U_ZERO_ERROR;
        length=uloc_getDisplayCountry(fullName, displayLocale.fullName,
                                      buffer, result.getCapacity(),
                                      &errorCode);
        result.releaseBuffer(U_SUCCESS(errorCode) ? length : 0);
    }

    return result;
}
