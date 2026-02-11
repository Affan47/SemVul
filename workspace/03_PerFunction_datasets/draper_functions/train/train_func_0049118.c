DateCalc_mktime(time_t *seconds,
                        Z_int year, Z_int month, Z_int day,
                        Z_int hour, Z_int min,   Z_int sec,
                        Z_int doy,  Z_int dow,   Z_int dst)
{
    struct tm date;

    *seconds = (time_t) 0;

#ifdef MACOS_TRADITIONAL
    if ( (year  < 1904) or (year  > 2040) or
#else
    if ( (year  < 1970) or (year  > 2038) or
#endif
         (month <    1) or (month >   12) or
         (day   <    1) or (day   >   31) or
         (hour  <    0) or (hour  >   23) or
         (min   <    0) or (min   >   59) or
         (sec   <    0) or (sec   >   59) )
    return(false);

#ifdef MACOS_TRADITIONAL
    if ( (year == 2040) and ( (month >  2) or
                            ( (month == 2) and ( (day >  6) or
                                               ( (day == 6) and ( (hour >  6) or
                                                                ( (hour == 6) and ( (min >  28) or
                                                                                  ( (min == 28) and (sec > 15) ) ))))))) )
    return(false);
#else
    if ( (year == 2038) and ( (month >  1) or
                            ( (month == 1) and ( (day >  19) or
                                               ( (day == 19) and ( (hour >  3) or
                                                                 ( (hour == 3) and ( (min >  14) or
                                                                                   ( (min == 14) and (sec > 7) ) ))))))) )
    return(false);
#endif

    year -= 1900;
    month--;
    if (doy <= 0) doy = -1;
    else          doy--;
    if (dow <= 0) dow = -1; else
    if (dow == 7) dow =  0;
    if (dst != 0)
    {
        if (dst < 0) dst = -1;
        else         dst =  1;
    }
    date.tm_year  = year;
    date.tm_mon   = month;
    date.tm_mday  = day;
    date.tm_hour  = hour;
    date.tm_min   = min;
    date.tm_sec   = sec;
    date.tm_yday  = doy;
    date.tm_wday  = dow;
    date.tm_isdst = dst;
    *seconds = mktime(&date);
    return(*seconds >= 0);
}
