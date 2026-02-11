open_log_file(const char * log_name) {
#if ENABLE_Trace
    if (log_name == NULL) {
        log_file = NULL;
    }
    else if (strcmp(log_name, "-") == 0) {
        log_file = stderr;
    }
    else if ((log_file = fopen(log_name, "a")) == NULL) {
        fprintf(stderr, "TCF: error: cannot create log file %s\n", log_name);
        exit(1);
    }
#endif
}
