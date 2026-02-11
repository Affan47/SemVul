get_tod(timeofday_t *tod) {
    tod->year = todtick/HOURS_PER_YEAR;
    tod->month = (todtick/HOURS_PER_MONTH)%MONTHS_PER_YEAR;
    tod->day = (todtick%HOURS_PER_MONTH)/DAYS_PER_MONTH;
    tod->dayofweek = tod->day%DAYS_PER_WEEK;
    tod->hour = todtick%HOURS_PER_DAY;
    tod->minute = (pticks%PTICKS_PER_CLOCK)/(PTICKS_PER_CLOCK/58);
    if (tod->minute > 58)
        tod->minute = 58;
    tod->weekofmonth = tod->day/WEEKS_PER_MONTH;
    if (tod->month < 3)
        tod->season = 0;
    else if (tod->month < 6)
        tod->season = 1;
    else if (tod->month < 9)
        tod->season = 2;
    else if (tod->month < 12)
        tod->season = 3;
    else
        tod->season = 4;

    if (tod->hour < 5)
        tod->periodofday = 0;
    else if (tod->hour < 8)
        tod->periodofday = 1;
    else if (tod->hour < 13)
        tod->periodofday = 2;
    else if (tod->hour < 15)
        tod->periodofday = 3;
    else if (tod->hour < 20)
        tod->periodofday = 4;
    else if (tod->hour < 23)
        tod->periodofday = 5;
    else
        tod->periodofday = 0;
}
