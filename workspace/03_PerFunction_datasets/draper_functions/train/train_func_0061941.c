isLeapYear(const tm& at) {
    int y = at.tm_year + TM_YEAR_BASE;
    return ((y % 4) == 0 && (y % 100) != 0 || (y % 400) == 0);
}
