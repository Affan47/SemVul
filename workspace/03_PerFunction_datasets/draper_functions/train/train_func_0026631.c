format(const DigitList &number,
                     UnicodeString& appendTo,
                     FieldPosition& pos,
                     UErrorCode &status) const {
    FieldPositionOnlyHandler handler(pos);
    _format(number, appendTo, handler, status);
    return appendTo;
}
