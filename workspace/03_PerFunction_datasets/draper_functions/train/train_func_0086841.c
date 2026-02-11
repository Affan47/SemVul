log_new(log_type_t type, const char *ident, const char *facility)
{
    log_t log;
    int fnum = 0;

    log = (log_t) calloc(1, sizeof(struct log_st));

    log->type = type;

    if(type == log_SYSLOG) {
        fnum = _log_facility(facility);
        if (fnum < 0)
            fnum = LOG_LOCAL7;
        openlog(ident, LOG_PID, fnum);
        return log;
    }

    else if(type == log_STDOUT) {
        log->file = stdout;
        return log;
    }

    log->file = fopen(ident, "a+");
    if(log->file == NULL)
    {
        fprintf(stderr,
            "ERROR: couldn't open logfile: %s\n"
            "       logging will go to stdout instead\n", strerror(errno));
        log->type = log_STDOUT;
        log->file = stdout;
    }

    return log;
}
