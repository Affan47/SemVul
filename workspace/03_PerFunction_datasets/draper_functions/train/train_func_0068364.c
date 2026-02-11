netsnmp_get_monotonic_clock(struct timeval* tv)
{
#if defined(HAVE_CLOCK_GETTIME) && defined(CLOCK_MONOTONIC)
    struct timespec ts;
    int res;

    res = clock_gettime(CLOCK_MONOTONIC, &ts);
    if (res >= 0) {
        tv->tv_sec = ts.tv_sec;
        tv->tv_usec = ts.tv_nsec / 1000;
    } else {
        netsnmp_assert(FALSE);
        memset(tv, 0, sizeof(*tv));
    }
#elif defined(WIN32)


    typedef ULONGLONG (WINAPI * pfGetTickCount64)(void);
    static int s_initialized;
    static pfGetTickCount64 s_pfGetTickCount64;
    uint64_t now64;

    if (!s_initialized) {
        HMODULE hKernel32 = GetModuleHandle("kernel32");
        s_pfGetTickCount64 =
            (pfGetTickCount64) GetProcAddress(hKernel32, "GetTickCount64");
        s_initialized = TRUE;
    }

    if (s_pfGetTickCount64) {

        now64 = (*s_pfGetTickCount64)();
    } else {

        static uint32_t s_wraps, s_last;
        uint32_t now;

        now = GetTickCount();
        if (now < s_last)
            s_wraps++;
        s_last = now;
        now64 = ((uint64_t)s_wraps << 32) | now;
    }
    tv->tv_sec = now64 / 1000;
    tv->tv_usec = (now64 % 1000) * 1000;
#else

#warning Not sure how to query a monotonically increasing clock on your system. \
Timers will not work correctly if the system clock is adjusted by e.g. ntpd.
    gettimeofday(tv, NULL);
#endif
}
