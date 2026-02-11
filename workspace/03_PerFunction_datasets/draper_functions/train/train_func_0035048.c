pygettimeofday(_PyTime_timeval *tp, _Py_clock_info_t *info)
{
#ifdef MS_WINDOWS
    FILETIME system_time;
    ULARGE_INTEGER large;
    ULONGLONG microseconds;

    GetSystemTimeAsFileTime(&system_time);
    large.u.LowPart = system_time.dwLowDateTime;
    large.u.HighPart = system_time.dwHighDateTime;


    microseconds = large.QuadPart / 10 - 11644473600000000;
    tp->tv_sec = microseconds / 1000000;
    tp->tv_usec = microseconds % 1000000;
    if (info) {
        DWORD timeAdjustment, timeIncrement;
        BOOL isTimeAdjustmentDisabled;

        info->implementation = "GetSystemTimeAsFileTime()";
        info->monotonic = 0;
        (void) GetSystemTimeAdjustment(&timeAdjustment, &timeIncrement,
                                       &isTimeAdjustmentDisabled);
        info->resolution = timeIncrement * 1e-7;
        info->adjustable = 1;
    }
#else


#ifdef HAVE_GETTIMEOFDAY
    int err;
#ifdef GETTIMEOFDAY_NO_TZ
    err = gettimeofday(tp);
#else
    err = gettimeofday(tp, (struct timezone *)NULL);
#endif
    if (err == 0) {
        if (info) {
            info->implementation = "gettimeofday()";
            info->resolution = 1e-6;
            info->monotonic = 0;
            info->adjustable = 1;
        }
        return;
    }
#endif

#if defined(HAVE_FTIME)
    {
        struct timeb t;
        ftime(&t);
        tp->tv_sec = t.time;
        tp->tv_usec = t.millitm * 1000;
        if (info) {
            info->implementation = "ftime()";
            info->resolution = 1e-3;
            info->monotonic = 0;
            info->adjustable = 1;
        }
    }
#else
    tp->tv_sec = time(NULL);
    tp->tv_usec = 0;
    if (info) {
        info->implementation = "time()";
        info->resolution = 1.0;
        info->monotonic = 0;
        info->adjustable = 1;
    }
#endif

#endif
}
