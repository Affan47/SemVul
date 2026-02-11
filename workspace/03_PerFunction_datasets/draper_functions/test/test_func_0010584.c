x509_time_expired( const x509_time *to )
{
    int year, mon, day;
    int hour, min, sec;

#if defined(_WIN32) && !defined(EFIX64) && !defined(EFI32)
    SYSTEMTIME st;

    GetLocalTime(&st);

    year = st.wYear;
    mon = st.wMonth;
    day = st.wDay;
    hour = st.wHour;
    min = st.wMinute;
    sec = st.wSecond;
#else
    struct tm *lt;
    time_t tt;

    tt = time( NULL );
    lt = localtime( &tt );

    year = lt->tm_year + 1900;
    mon = lt->tm_mon + 1;
    day = lt->tm_mday;
    hour = lt->tm_hour;
    min = lt->tm_min;
    sec = lt->tm_sec;
#endif

    if( year  > to->year )
        return( 1 );

    if( year == to->year &&
        mon   > to->mon )
        return( 1 );

    if( year == to->year &&
        mon  == to->mon  &&
        day   > to->day )
        return( 1 );

    if( year == to->year &&
        mon  == to->mon  &&
        day  == to->day  &&
        hour  > to->hour )
        return( 1 );

    if( year == to->year &&
        mon  == to->mon  &&
        day  == to->day  &&
        hour == to->hour &&
        min   > to->min  )
        return( 1 );

    if( year == to->year &&
        mon  == to->mon  &&
        day  == to->day  &&
        hour == to->hour &&
        min  == to->min  &&
        sec   > to->sec  )
        return( 1 );

    return( 0 );
}
