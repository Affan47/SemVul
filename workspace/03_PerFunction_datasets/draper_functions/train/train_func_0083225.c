gmtimew(wideval_t timew, struct vtm *result)
{
    time_t t;
    struct tm tm;
    VALUE subsecx;
    wideval_t timew2;

    if (wlt(timew, WINT2FIXWV(0))) {
        gmtimew_noleapsecond(timew, result);
        return result;
    }

    init_leap_second_info();

    if (wlt(rb_time_magnify(TIMET2WV(known_leap_seconds_limit)), timew)) {
        timew = wsub(timew, rb_time_magnify(WINT2WV(number_of_leap_seconds_known)));
        gmtimew_noleapsecond(timew, result);
        return result;
    }

    split_second(timew, &timew2, &subsecx);

    t = WV2TIMET(timew2);
    if (!gmtime_with_leapsecond(&t, &tm))
        return NULL;

    result->year = LONG2NUM((long)tm.tm_year + 1900);
    result->mon = tm.tm_mon + 1;
    result->mday = tm.tm_mday;
    result->hour = tm.tm_hour;
    result->min = tm.tm_min;
    result->sec = tm.tm_sec;
    result->subsecx = subsecx;
    result->utc_offset = INT2FIX(0);
    result->wday = tm.tm_wday;
    result->yday = tm.tm_yday+1;
    result->isdst = tm.tm_isdst;
    result->zone = "UTC";

    return result;
}
