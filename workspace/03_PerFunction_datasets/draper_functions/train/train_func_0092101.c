crm_time_log_alias(int log_level, const char *file, const char *function, int line,
                   const char *prefix, crm_time_t * date_time, int flags)
{
    char *date_s = crm_time_as_string(date_time, flags);

    if (log_level < LOG_CRIT) {
        printf("%s%s%s\n",
               prefix ? prefix : "", prefix ? ": " : "", date_s ? date_s : "__invalid_date__");
    } else {
        do_crm_log_alias(log_level, file, function, line, "%s%s%s",
                         prefix ? prefix : "", prefix ? ": " : "",
                         date_s ? date_s : "__invalid_date__");
    }
    free(date_s);
}
