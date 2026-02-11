formatMeasure(
        const Measure &measure,
        const NumberFormat &nf,
        UnicodeString &appendTo,
        FieldPosition &pos,
        UErrorCode &status) const {
    if (U_FAILURE(status)) {
        return appendTo;
    }
    const Formattable& amtNumber = measure.getNumber();
    const MeasureUnit& amtUnit = measure.getUnit();
    if (isCurrency(amtUnit)) {
        UChar isoCode[4];
        u_charsToUChars(amtUnit.getSubtype(), isoCode, 4);
        return cache->getCurrencyFormat(widthToIndex(width))->format(
                new CurrencyAmount(amtNumber, isoCode, status),
                appendTo,
                pos,
                status);
    }
    const QuantityFormatter *quantityFormatter = getQuantityFormatter(
            amtUnit.getIndex(), widthToIndex(width), status);
    if (U_FAILURE(status)) {
        return appendTo;
    }
    return quantityFormatter->format(
            amtNumber,
            nf,
            **pluralRules,
            appendTo,
            pos,
            status);
}
