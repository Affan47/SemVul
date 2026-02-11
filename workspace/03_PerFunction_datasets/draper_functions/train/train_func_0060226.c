fs_timegm(struct tm *tm) {
    if (g_mutex) {
        fs_mutex_lock(g_mutex);
    }
    time_t ret;

    char *tz;
#ifdef WINDOWS
    tz = getenv("TZ");
    if (tz) {
        tz = fs_strdup_printf("TZ=%s", tz);
    }
    else {
        tz = fs_strdup("TZ=");
    }
    _putenv("TZ=GMT");
    _tzset();
    ret = mktime(tm);

    _putenv(tz);
    free(tz);
    _tzset();
#else
    tz = getenv("TZ");
    setenv("TZ", "", 1);
    tzset();
    ret = mktime(tm);
    if (tz) {
        setenv("TZ", tz, 1);
    }
    else {
        unsetenv("TZ");
    }
    tzset();
#endif
    if (g_mutex) {
        fs_mutex_unlock(g_mutex);
    }
    return ret;
}
