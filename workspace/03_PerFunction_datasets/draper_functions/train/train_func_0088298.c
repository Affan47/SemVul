lock_state(const char * argv0) {
    FILE *lock_fp;
    lock_fp = fopen(lockfile, no_act ? "r" : "a+");
    if (lock_fp == NULL) {
        if (!no_act) {
            fprintf(stderr, "%s: failed to open lockfile %s: %s\n", argv0, lockfile, strerror(errno));
            exit(1);
        } else {
            return NULL;
        }
    }

    int flags;

    if ((flags = fcntl(fileno(lock_fp), F_GETFD)) < 0 || fcntl(fileno(lock_fp), F_SETFD, flags | FD_CLOEXEC) < 0) {
        fprintf(stderr, "%s: failed to set FD_CLOEXEC on lockfile %s: %s\n", argv0, lockfile, strerror(errno));
        exit(1);
    }

    if (lock_fd(fileno(lock_fp)) < 0) {
        if (!no_act) {
            fprintf(stderr, "%s: failed to lock lockfile %s: %s\n", argv0, lockfile, strerror(errno));
            exit(1);
        }
    }

    return lock_fp;
}
