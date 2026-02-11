timedWait(int time)
{

#ifdef CBC_PTHREAD
    struct timespec absTime;
    my_gettime(&absTime);
    if (time > 0) {
        absTime.tv_nsec += time;
        if (absTime.tv_nsec >= 1000000000) {
            absTime.tv_nsec -= 1000000000;
            absTime.tv_sec++;
        }
    } else {
        absTime.tv_sec -= time;
    }
    pthread_cond_timedwait(&condition2_, &mutex2_, &absTime);
#else
#endif
}
