log_write(log_t log, int level, const char *msgfmt, ...)
{
    va_list ap;
    char *pos, message[MAX_LOG_LINE+1];
    int sz, len;
    time_t t;

    if(log && log->type == log_SYSLOG) {
        va_start(ap, msgfmt);
#ifdef HAVE_VSYSLOG
        vsyslog(level, msgfmt, ap);
#else
        len = vsnprintf(message, MAX_LOG_LINE, msgfmt, ap);
        if (len > MAX_LOG_LINE)
            message[MAX_LOG_LINE] = '\0';
        else
            message[len] = '\0';
        syslog(level, "%s", message);
#endif
        va_end(ap);

#ifndef DEBUG
        return;
#endif
    }


    t = time(NULL);
    pos = ctime(&t);
    sz = strlen(pos);

    pos[sz-1]=' ';


    len = snprintf(message, MAX_LOG_LINE, "%s[%s] ", pos, _log_level[level]);
    if (len > MAX_LOG_LINE)
        message[MAX_LOG_LINE] = '\0';
    else
        message[len] = '\0';


    for (pos = message; *pos != '\0'; pos++);
    sz = pos - message;
    va_start(ap, msgfmt);
    vsnprintf(pos, MAX_LOG_LINE - sz, msgfmt, ap);
    va_end(ap);
#ifndef DEBUG
    if(log && log->type != log_SYSLOG) {
#endif
        if(log && log->file) {
            fprintf(log->file,"%s", message);
            fprintf(log->file, "\n");
            fflush(log->file);
	    }
#ifndef DEBUG
    }
#endif

#ifdef DEBUG
    if (!debug_log_target) {
        debug_log_target = stderr;
    }

    if ((log == 0) || (get_debug_flag() && log->type != log_STDOUT)) {
        fprintf(debug_log_target, "%s\n", message);
        fflush(debug_log_target);
    }
#endif
}
