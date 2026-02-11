log_err_status(UErrorCode status, const char* pattern, ...)
{
    va_list ap;
    va_start(ap, pattern);

    if ((status == U_FILE_ACCESS_ERROR || status == U_MISSING_RESOURCE_ERROR)) {
        ++DATA_ERROR_COUNT;

        if (WARN_ON_MISSING_DATA == 0) {

            if (strchr(pattern, '\n') != NULL) {
                ++ERROR_COUNT;
            }
            vlog_err(NULL, pattern, ap);
        } else {
            vlog_info("[DATA] ", pattern, ap);
        }
    } else {

        if(strchr(pattern, '\n') != NULL) {
            ++ERROR_COUNT;
        }
        vlog_err(NULL, pattern, ap);
    }
}
