qlog(const char *filepathfmt, mode_t mode, int rotateinterval,
             int options) {
    qlog_t *log;


    log = (qlog_t *) calloc(1, sizeof(qlog_t));
    if (log == NULL) {
        errno = ENOMEM;
        return NULL;
    }


    qstrcpy(log->filepathfmt, sizeof(log->filepathfmt), filepathfmt);
    log->mode = mode;
    if (rotateinterval > 0)
        log->rotateinterval = rotateinterval;


    if (options & QLOG_OPT_THREADSAFE) {
        Q_MUTEX_NEW(log->qmutex, true);
        if (log->qmutex == NULL) {
            errno = ENOMEM;
            free(log);
            return NULL;
        }
    }
    if (options & QLOG_OPT_FLUSH) {
        log->logflush = true;
    }


    if (_real_open(log) == false) {
        free(log);
        Q_MUTEX_DESTROY(log->qmutex);
        return NULL;
    }


    log->write = write_;
    log->writef = writef;
    log->duplicate = duplicate;
    log->flush = flush_;
    log->free = free_;

    return log;
}
