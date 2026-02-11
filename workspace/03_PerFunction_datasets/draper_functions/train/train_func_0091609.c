storePid(void)
{
    int oldpid;

    if (pidFile[0] != '\0') {
        pidFd = open(pidFile, O_RDWR);
        if (pidFd == -1 && errno == ENOENT)
            pidFd = open(pidFile, O_RDWR | O_CREAT, 0666);
        if (pidFd == -1 || !(pidFilePtr = fdopen(pidFd, "r+"))) {
            logError("process-id file %s cannot be opened\n",
                     pidFile);
            return -1;
        }
        if (fscanf(pidFilePtr, "%d\n", &oldpid) != 1)
            oldpid = -1;
        fseek(pidFilePtr, 0l, 0);
        if (lockPidFile) {
#ifdef F_SETLK
# ifndef SEEK_SET
#  define SEEK_SET 0
# endif
            struct flock lock_data;
            lock_data.l_type = F_WRLCK;
            lock_data.l_whence = SEEK_SET;
            lock_data.l_start = lock_data.l_len = 0;
            if (fcntl(pidFd, F_SETLK, &lock_data) == -1) {
                if (errno == EAGAIN)
                    return oldpid;
                else
                    return -1;
            }
#else
# ifdef LOCK_EX
            if (flock(pidFd, LOCK_EX | LOCK_NB) == -1) {
                if (errno == EWOULDBLOCK)
                    return oldpid;
                else
                    return -1;
            }
# else
            if (lockf(pidFd, F_TLOCK, 0) == -1) {
                if (errno == EACCES)
                    return oldpid;
                else
                    return -1;
            }
# endif
#endif
        }
        fprintf(pidFilePtr, "%ld\n", (long)getpid());
        if (fflush(pidFilePtr) == EOF)
            logError("Cannot write PID file %s: %m", pidFile);
        registerCloseOnFork(pidFd);
    }
    return 0;
}
