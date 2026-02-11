daysInMonth(int year, int month) const
{
    if (month == 1) {
        if (isLeapYear(year)) {
            return 31;
        } else {
            return 30;
        }
    }

    if (month >= 2 && month <= 6) {
        return 31;
    }

    return 30;
}
