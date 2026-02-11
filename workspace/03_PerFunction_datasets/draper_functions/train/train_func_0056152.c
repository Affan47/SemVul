mult(const DigitList &other, UErrorCode &status) {
    fContext.status = 0;
    int32_t requiredDigits = this->digits() + other.digits();
    if (requiredDigits > fContext.digits) {
        reduce();
        int32_t requiredDigits = this->digits() + other.digits();
        ensureCapacity(requiredDigits, status);
    }
    uprv_decNumberMultiply(fDecNumber, fDecNumber, other.fDecNumber, &fContext);
    fHaveDouble = FALSE;
}
