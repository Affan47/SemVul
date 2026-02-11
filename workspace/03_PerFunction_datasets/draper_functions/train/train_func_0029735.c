initCapitalizationContextInfo(const Locale& thelocale)
{
#if !UCONFIG_NO_BREAK_ITERATION
    const char * localeID = (thelocale != NULL)? thelocale.getBaseName(): NULL;
    UErrorCode status = U_ZERO_ERROR;
    UResourceBundle *rb = ures_open(NULL, localeID, &status);
    rb = ures_getByKeyWithFallback(rb, "contextTransforms", rb, &status);
    rb = ures_getByKeyWithFallback(rb, "relative", rb, &status);
    if (U_SUCCESS(status) && rb != NULL) {
        int32_t len = 0;
        const int32_t * intVector = ures_getIntVector(rb, &len, &status);
        if (U_SUCCESS(status) && intVector != NULL && len >= 2) {
            fCapitalizationOfRelativeUnitsForUIListMenu = intVector[0];
            fCapitalizationOfRelativeUnitsForStandAlone = intVector[1];
        }
    }
    ures_close(rb);
#endif
}
