format(UDate date, UnicodeString& appendTo, FieldPosition& fieldPosition) const {
    if (fCalendar != NULL) {

        UErrorCode ec = U_ZERO_ERROR;
        fCalendar->setTime(date, ec);
        if (U_SUCCESS(ec)) {
            return format(*fCalendar, appendTo, fieldPosition);
        }
    }
    return appendTo;
}
