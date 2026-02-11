tm_to_time(struct tm *tm, time_t *time)
{
struct		tm ttm;
time_t		res, dst;


    memcpy(&ttm, tm, sizeof(ttm));
    ttm.tm_isdst = -1;
    pthread_mutex_lock(&mktime_lock);
    res = mktime(&ttm);
    pthread_mutex_unlock(&mktime_lock);
    dst = 0;
    if ( ttm.tm_isdst > 0)
            dst = -3600;
#if	defined(SOLARIS) || defined(_AIX)
    res -= timezone + dst;
#elif	defined(_WIN32)
    res -= _timezone + dst;
#elif	defined(FREEBSD) || (defined(LINUX) && !defined(HAVE_STRUCT_TM___TM_GMTOFF__) )
    res += ttm.tm_gmtoff;
#elif	defined(HAVE_STRUCT_TM___TM_GMTOFF__)
    res += ttm.__tm_gmtoff__ - dst;
#else
    res += ttm.tm_gmtoff - dst;
#endif
    return(*time = res);
}
