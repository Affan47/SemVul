format(
        double quantity, UDateDirection direction, UDateRelativeUnit unit,
        UnicodeString& appendTo, UErrorCode& status) const {
    if (U_FAILURE(status)) {
        return appendTo;
    }
    if (direction != UDAT_DIRECTION_LAST && direction != UDAT_DIRECTION_NEXT) {
        status = U_ILLEGAL_ARGUMENT_ERROR;
        return appendTo;
    }
    int32_t bFuture = direction == UDAT_DIRECTION_NEXT ? 1 : 0;
    FieldPosition pos(FieldPosition::DONT_CARE);
    return cache->relativeUnits[unit][bFuture].format(
            quantity,
            **numberFormat,
            **pluralRules,
            appendTo,
            pos,
            status);
}
