getFixedDecimal(double number, UErrorCode &status) const {
    FixedDecimal result;

    if (U_FAILURE(status)) {
        return result;
    }

    if (uprv_isNaN(number) || uprv_isPositiveInfinity(fabs(number))) {

        result.init(number);
        return result;
    }

    if (fMultiplier == NULL && fScale == 0 && fRoundingIncrement == 0 && areSignificantDigitsUsed() == FALSE &&
            result.quickInit(number) && result.visibleDecimalDigitCount <= getMaximumFractionDigits()) {


        result.adjustForMinFractionDigits(getMinimumFractionDigits());
    } else {


        DigitList digits;
        digits.set(number);
        result = getFixedDecimal(digits, status);
    }
    return result;
}
