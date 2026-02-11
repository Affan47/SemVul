convert_date(const char *date)
{
    int year, mon, day, hour, min, sec, tzHours, tzMins;
    char tz;

    if (!parseDateString(date, &year, &mon, &day, &hour, &min, &sec,
                               &tz, &tzHours, &tzMins)) {
        return time_type(-1);
    }

    struct tm time;
    time.tm_sec = sec;
    time.tm_min = min;
    time.tm_hour = hour;
    time.tm_mday = day;
    time.tm_mon = mon - 1;
    time.tm_year = year - 1900;
    time.tm_wday = -1;
    time.tm_yday = -1;
    time.tm_isdst = -1;
    return mktime(&time);
}
