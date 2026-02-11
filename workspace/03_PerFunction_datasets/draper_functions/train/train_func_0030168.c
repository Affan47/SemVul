precision() const {
    if (areSignificantDigitsUsed()) {
        return getMaximumSignificantDigits();
    } else if (fUseExponentialNotation) {
        return getMinimumIntegerDigits() + getMaximumFractionDigits();
    } else {
        return getMaximumFractionDigits();
    }
}
