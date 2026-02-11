bdb_dl_detect_thread(void *arg)
{
    DB_ENV *dbenv;
    struct timeval t;
    dbenv = arg;
    if (settings.verbose > 1) {
        dbenv->errx(dbenv, "deadlock detecting thread created: %lu, every %d millisecond",
                           (u_long)pthread_self(), bdb_settings.dldetect_val);
    }
    while (!daemon_quit) {
        t.tv_sec = 0;
        t.tv_usec = bdb_settings.dldetect_val;
        (void)dbenv->lock_detect(dbenv, 0, DB_LOCK_YOUNGEST, NULL);

        (void)select(0, NULL, NULL, NULL, &t);
    }
    return (NULL);
}
