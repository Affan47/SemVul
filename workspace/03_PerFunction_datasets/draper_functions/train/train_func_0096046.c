boinc_fopen(const char* const path, const char* mode) {


    if (strchr(mode, 'r')) {
        if (!boinc_file_exists(path)) {
            return 0;
        }
    }
#ifndef _USING_FCGI_
    FILE *f = fopen(path, mode);
#else
    FCGI_FILE *f = FCGI::fopen(path,mode);
#endif

#ifdef _WIN32


    if (!f) {
        double start = dtime();
        do {
            boinc_sleep(drand()*2);
            f = _fsopen(path, mode, _SH_DENYNO);

            if (f) break;
        } while (dtime() < start + FILE_RETRY_INTERVAL);
    }
#else


    if (!f) {
        for (int i=0; i<5; i++) {
            boinc_sleep(drand());
            if (errno != EINTR) break;
#ifndef _USING_FCGI_
            f = fopen(path, mode);
#else
            f = FCGI::fopen(path, mode);
#endif
            if (f) break;
        }
    }
    if (f) {
        fcntl(fileno(f), F_SETFD, FD_CLOEXEC);
    }
#endif
    return f;
}
