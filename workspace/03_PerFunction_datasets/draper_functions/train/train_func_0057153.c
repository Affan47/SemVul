setMinimumSignificantDigits(int32_t min) {
    if (min < 1) {
        min = 1;
    }

    int32_t max = _max(fMaxSignificantDigits, min);
    fMinSignificantDigits = min;
    fMaxSignificantDigits = max;
#if UCONFIG_FORMAT_FASTPATHS_49
    handleChanged();
#endif
}
