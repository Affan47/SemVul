getGMTOffsetDigits(UnicodeString& digits) const {
    digits.remove();
    for (int32_t i = 0; i < 10; i++) {
        digits.append(fGMTOffsetDigits[i]);
    }
    return digits;
}
