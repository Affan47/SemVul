setMeasureFormatLocale(const Locale &locale, UErrorCode &status) {
    if (U_FAILURE(status) || locale == getLocale(status)) {
        return FALSE;
    }
    initMeasureFormat(locale, width, NULL, status);
    return U_SUCCESS(status);
}
