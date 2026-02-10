globus_l_gram_audit_write_timestamp(
    FILE *                              f,
    time_t                              when,
    const char *                        delim)
{
    int                                 rc;
    char *                              t;
    char *                              tmp;
    struct tm                           tmv;
    struct tm *                         tm_p;
#ifndef BUILD_LITE
    char tbuf[26];
#endif

    if (when == 0)
    {
        rc = fprintf(f, "\"NULL\"%s", delim);
        return rc >= 0 ? GLOBUS_SUCCESS : GLOBUS_GRAM_PROTOCOL_ERROR_NO_RESOURCES;
    }
    tm_p = globus_libc_gmtime_r(&when, &tmv);
    if (tm_p == NULL)
    {
        return GLOBUS_GRAM_PROTOCOL_ERROR_NO_RESOURCES;
    }
    t = asctime_r(tm_p, tbuf);
    if (t == NULL)
    {
        return GLOBUS_GRAM_PROTOCOL_ERROR_NO_RESOURCES;
    }
    tmp = strchr(t, '\n');
    if (tmp)
    {
       *tmp = '\0';
    }
    tmp = strrchr(t, ' ');
    *tmp = '\0';

    rc = fprintf(f, "\"%s UTC %s\"%s", t, tmp+1, delim);

    return rc >= 0 ? GLOBUS_SUCCESS : GLOBUS_GRAM_PROTOCOL_ERROR_NO_RESOURCES;
}
