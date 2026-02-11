getLimit(UCalendarDateFields field, ELimitType limitType) const {
    switch (field) {
    case UCAL_DAY_OF_WEEK:
    case UCAL_AM_PM:
    case UCAL_HOUR:
    case UCAL_HOUR_OF_DAY:
    case UCAL_MINUTE:
    case UCAL_SECOND:
    case UCAL_MILLISECOND:
    case UCAL_ZONE_OFFSET:
    case UCAL_DST_OFFSET:
    case UCAL_DOW_LOCAL:
    case UCAL_JULIAN_DAY:
    case UCAL_MILLISECONDS_IN_DAY:
    case UCAL_IS_LEAP_MONTH:
        return kCalendarLimits[field][limitType];

    case UCAL_WEEK_OF_MONTH:
        {
            int32_t limit;
            if (limitType == UCAL_LIMIT_MINIMUM) {
                limit = getMinimalDaysInFirstWeek() == 1 ? 1 : 0;
            } else if (limitType == UCAL_LIMIT_GREATEST_MINIMUM) {
                limit = 1;
            } else {
                int32_t minDaysInFirst = getMinimalDaysInFirstWeek();
                int32_t daysInMonth = handleGetLimit(UCAL_DAY_OF_MONTH, limitType);
                if (limitType == UCAL_LIMIT_LEAST_MAXIMUM) {
                    limit = (daysInMonth + (7 - minDaysInFirst)) / 7;
                } else {
                    limit = (daysInMonth + 6 + (7 - minDaysInFirst)) / 7;
                }
            }
            return limit;
        }
    default:
        return handleGetLimit(field, limitType);
    }
}
