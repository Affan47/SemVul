vslapd_log_access(char *fmt, va_list ap)
{
    time_t	tnl;
    long	tz;
    struct tm	*tmsp, tms;
    char	tbuf[ TBUFSIZE ];
    char	sign;
    char	buffer[SLAPI_LOG_BUFSIZ];
    char	vbuf[SLAPI_LOG_BUFSIZ];
    int		blen, vlen;

    static time_t	old_time = 0;
    static char		old_tbuf[SLAPI_LOG_BUFSIZ];
	static int old_blen = 0;

    tnl = current_time();


    PR_Lock(ts_time_lock);
    if (tnl == old_time) {
        strcpy(buffer, old_tbuf);
        blen = old_blen;
        PR_Unlock(ts_time_lock);
    } else {

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
        sprintf( buffer, "[%s %c%02d%02d] ", tbuf, sign,
                (int)( tz / 3600 ), (int)( tz % 3600));
        old_time = tnl;
        strcpy(old_tbuf, buffer);
        blen = strlen(buffer);
        old_blen = blen;
        PR_Unlock(ts_time_lock);
    }

    vlen = PR_vsnprintf(vbuf, SLAPI_LOG_BUFSIZ, fmt, ap);
    if (! vlen) {
        return -1;
    }

    if (SLAPI_LOG_BUFSIZ - blen < vlen) {
        return -1;
    }

    log_append_buffer2(tnl, loginfo.log_access_buffer, buffer, blen, vbuf, vlen);

    return( 0 );
}
