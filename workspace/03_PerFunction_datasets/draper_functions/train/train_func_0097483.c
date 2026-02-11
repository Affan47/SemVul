libspamc_log (int flags, int level, char *msg, ...)
{
    va_list ap;
    char buf[LOG_BUFSIZ+1];
    int len = 0;

    va_start(ap, msg);

    if ((flags & SPAMC_LOG_TO_STDERR) != 0) {

        len = snprintf(buf, LOG_BUFSIZ, "spamc: ");
        len += vsnprintf(buf+len, LOG_BUFSIZ-len, msg, ap);


        if (len > (LOG_BUFSIZ-2)) { len = (LOG_BUFSIZ-3); }

        len += snprintf(buf+len, LOG_BUFSIZ-len, "\n");
        buf[LOG_BUFSIZ] = '\0';
        if (write (2, buf, len) != len)
		goto out;
    } else {
        vsnprintf(buf, LOG_BUFSIZ, msg, ap);
        buf[LOG_BUFSIZ] = '\0';
#ifndef _WIN32
        syslog (level, "%s", buf);
#else
        (void) level;
        g_printerr ("%s\n", buf);
#endif
    }
out:
    va_end(ap);
}
