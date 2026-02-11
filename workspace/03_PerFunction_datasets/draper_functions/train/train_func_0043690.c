log_entry(char *component, int level, const char *format, ...) {
    if (level < 0 || level > 7 || level > loglevel)
        return;

    va_list ap;
    va_start(ap, format);

    if (logfile) {

        struct tm *ptr;
        time_t lt;
        char timestr[20];
        lt = time(NULL);
        ptr = localtime(&lt);
        strftime(timestr, sizeof(timestr), "%b %e %H:%M:%S", ptr);

        fprintf(logfile, "%s: [%s] %s: ", timestr, component, LOG_LEVEL_NAMES[level]);
        vfprintf(logfile, format, ap);
        fprintf(logfile, "\n");
    } else {
        vsyslog(level, format, ap);
    }

    va_end(ap);
}
