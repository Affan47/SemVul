modperl_trace_level_set(apr_file_t *logfile, const char *level)
{
    if (!level) {
        if (!(level = getenv("MOD_PERL_TRACE"))) {
            return;
        }
    }
    debug_level = 0x0;

    if (strcasecmp(level, "all") == 0) {
        debug_level = 0xffffffff;
    }
    else if (apr_isalpha(level[0])) {
        static char debopts[] = MP_TRACE_OPTS;
        char *d;

        for (; *level && (d = strchr(debopts, *level)); level++) {
            debug_level |= 1 << (d - debopts);
        }
    }
    else {
        debug_level = atoi(level);
    }

    debug_level |= 0x80000000;

    modperl_trace_logfile_set(logfile);

    MP_TRACE_any_do(MP_TRACE_dump_flags());
}
