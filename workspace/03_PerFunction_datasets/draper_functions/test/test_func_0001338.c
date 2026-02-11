profile_passed_limit(tm)
    proftime_T	*tm;
{
    proftime_T	now;

# ifdef WIN3264
    if (tm->QuadPart == 0)
	return FALSE;
    QueryPerformanceCounter(&now);
    return (now.QuadPart > tm->QuadPart);
# else
    if (tm->tv_sec == 0)
	return FALSE;
    gettimeofday(&now, NULL);
    return (now.tv_sec > tm->tv_sec
	    || (now.tv_sec == tm->tv_sec && now.tv_usec > tm->tv_usec));
# endif
}
