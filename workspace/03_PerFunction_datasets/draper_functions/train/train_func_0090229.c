format(const Formattable* objs,
                     int32_t cnt,
                     UnicodeString& appendTo,
                     FieldPosition& pos,
                     UErrorCode& status) const
{
    if(cnt < 0) {
        status = U_ILLEGAL_ARGUMENT_ERROR;
        return appendTo;
    }
    if (msgPattern.countParts() == 0) {
        status = U_INVALID_STATE_ERROR;
        return appendTo;
    }

    for (int32_t i = 0; i < cnt; i++) {
        double objDouble = objs[i].getDouble(status);
        if (U_SUCCESS(status)) {
            format(objDouble, appendTo, pos);
        }
    }

    return appendTo;
}
