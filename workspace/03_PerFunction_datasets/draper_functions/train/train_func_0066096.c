setCurrencyInternally(const UChar* theCurrency,
                                          UErrorCode& ec) {


    UBool isCurr = (theCurrency && *theCurrency);

    double rounding = 0.0;
    int32_t frac = 0;
    if (fCurrencySignCount != fgCurrencySignCountZero && isCurr) {
        rounding = ucurr_getRoundingIncrement(theCurrency, &ec);
        frac = ucurr_getDefaultFractionDigits(theCurrency, &ec);
    }

    NumberFormat::setCurrency(theCurrency, ec);
    if (U_FAILURE(ec)) return;

    if (fCurrencySignCount != fgCurrencySignCountZero) {

        if (isCurr) {
            setRoundingIncrement(rounding);
            setMinimumFractionDigits(frac);
            setMaximumFractionDigits(frac);
        }
        expandAffixes(NULL);
    }
#if UCONFIG_FORMAT_FASTPATHS_49
    handleChanged();
#endif
}
