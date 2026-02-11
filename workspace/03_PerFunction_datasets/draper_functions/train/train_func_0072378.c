vslapd_log_emergency_error(LOGFD fp, const char *msg, int locked)
{
    time_t    tnl;
    long      tz;
    struct tm *tmsp, tms;
    char      tbuf[ TBUFSIZE ];
    char      buffer[SLAPI_LOG_BUFSIZ];
    char      sign;
    int       size;

    tnl = current_time();
#ifdef _WIN32
    {
        struct tm *pt = localtime( &tnl );
        tmsp = &tms;
        memcpy(&tms, pt, sizeof(struct tm) );
    }
#else
    (void)localtime_r( &tnl, &tms );
    tmsp = &tms;
#endif
#ifdef BSD_TIME
    tz = tmsp->tm_gmtoff;
#else
    tz = - timezone;
    if ( tmsp->tm_isdst ) {
        tz += 3600;
    }
#endif
    sign = ( tz >= 0 ? '+' : '-' );
    if ( tz < 0 ) {
        tz = -tz;
    }
    (void)strftime( tbuf, (size_t)TBUFSIZE, "%d/%b/%Y:%H:%M:%S", tmsp);
    sprintf( buffer, "[%s %c%02d%02d] - %s", tbuf, sign, (int)( tz / 3600 ), (int)( tz % 3600 ), msg);
    size = strlen(buffer);

    if(!locked)
        LOG_ERROR_LOCK_WRITE();

    slapi_write_buffer((fp), (buffer), (size));
    PR_Sync(fp);

    if(!locked)
        LOG_ERROR_UNLOCK_WRITE();
}
