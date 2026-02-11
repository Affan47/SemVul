TimedWait(long usec)
{
    ThrowIf(!pthread_equal(pthread_self(), fOwner), JackException("JackPosixProcessSync::TimedWait: a thread has to have locked a mutex before it can wait"));
    fOwner = 0;

    struct timeval T0, T1;
    timespec time;
    struct timeval now;
    int res;

    jack_log("JackPosixProcessSync::TimedWait time out = %ld", usec);
    gettimeofday(&T0, 0);

    gettimeofday(&now, 0);
    unsigned int next_date_usec = now.tv_usec + usec;
    time.tv_sec = now.tv_sec + (next_date_usec / 1000000);
    time.tv_nsec = (next_date_usec % 1000000) * 1000;

    res = pthread_cond_timedwait(&fCond, &fMutex, &time);
    if (res != 0) {
        jack_error("JackPosixProcessSync::TimedWait error usec = %ld err = %s", usec, strerror(res));
    } else {
        fOwner = pthread_self();
    }

    gettimeofday(&T1, 0);
    jack_log("JackPosixProcessSync::TimedWait finished delta = %5.1lf",
             (1e6 * T1.tv_sec - 1e6 * T0.tv_sec + T1.tv_usec - T0.tv_usec));

    return (res == 0);
}
