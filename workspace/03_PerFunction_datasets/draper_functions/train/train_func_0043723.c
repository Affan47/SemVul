formatMeasures(
        const Measure *measures,
        int32_t measureCount,
        UnicodeString &appendTo,
        FieldPosition &pos,
        UErrorCode &status) const {
    if (U_FAILURE(status)) {
        return appendTo;
    }
    if (measureCount == 0) {
        return appendTo;
    }
    if (measureCount == 1) {
        return formatMeasure(measures[0], **numberFormat, appendTo, pos, status);
    }
    if (width == UMEASFMT_WIDTH_NUMERIC) {
        Formattable hms[3];
        int32_t bitMap = toHMS(measures, measureCount, hms, status);
        if (bitMap > 0) {
            return formatNumeric(hms, bitMap, appendTo, status);
        }
    }
    if (pos.getField() != FieldPosition::DONT_CARE) {
        return formatMeasuresSlowTrack(
                measures, measureCount, appendTo, pos, status);
    }
    UnicodeString *results = new UnicodeString[measureCount];
    if (results == NULL) {
        status = U_MEMORY_ALLOCATION_ERROR;
        return appendTo;
    }
    for (int32_t i = 0; i < measureCount; ++i) {
        const NumberFormat *nf = cache->getIntegerFormat();
        if (i == measureCount - 1) {
            nf = numberFormat->get();
        }
        formatMeasure(
                measures[i],
                *nf,
                results[i],
                pos,
                status);
    }
    listFormatter->format(results, measureCount, appendTo, status);
    delete [] results;
    return appendTo;
}
