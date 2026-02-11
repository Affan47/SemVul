handleGetMonthLength(int32_t extendedYear, int32_t month)  const
{


    if (month < 0 || month > 11) {
        extendedYear += ClockMath::floorDivide(month, 12, month);
    }

    return isLeapYear(extendedYear) ? kLeapMonthLength[month] : kMonthLength[month];
}
