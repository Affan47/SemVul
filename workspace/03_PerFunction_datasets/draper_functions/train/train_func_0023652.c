getActualMaximum(UCalendarDateFields field, UErrorCode& status) const
{
    int32_t result;
    switch (field) {
    case UCAL_DATE:
        {
            if(U_FAILURE(status)) return 0;
            Calendar *cal = clone();
            if(!cal) { status = U_MEMORY_ALLOCATION_ERROR; return 0; }
            cal->prepareGetActual(field,FALSE,status);
            result = handleGetMonthLength(cal->get(UCAL_EXTENDED_YEAR, status), cal->get(UCAL_MONTH, status));
            delete cal;
        }
        break;

    case UCAL_DAY_OF_YEAR:
        {
            if(U_FAILURE(status)) return 0;
            Calendar *cal = clone();
            if(!cal) { status = U_MEMORY_ALLOCATION_ERROR; return 0; }
            cal->prepareGetActual(field,FALSE,status);
            result = handleGetYearLength(cal->get(UCAL_EXTENDED_YEAR, status));
            delete cal;
        }
        break;

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

        result = getMaximum(field);
        break;

    default:

        result = getActualHelper(field, getLeastMaximum(field), getMaximum(field),status);
        break;
    }
    return result;
}
