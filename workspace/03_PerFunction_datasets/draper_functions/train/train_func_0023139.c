dayOfWeekInMonth(int32_t year, int32_t month, int32_t dom) {
    int32_t weekInMonth = (dom + 6)/7;
    if (weekInMonth == 4) {
        if (dom + 7 > monthLength(year, month)) {
            weekInMonth = -1;
        }
    } else if (weekInMonth == 5) {
        weekInMonth = -1;
    }
    return weekInMonth;
}
