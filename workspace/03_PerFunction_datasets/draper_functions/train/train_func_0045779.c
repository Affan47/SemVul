np_multi()
{
    int i;
    sys_thread_t *tid;
    pthread_t me = pthread_self();

    tid = ThreadQueue;
    for (i = 0; i < ActiveThreadCount && tid != 0; i++) {
        if ((tid->sys_thread != me) && (tid->state != SUSPENDED)) {
            np_continue(tid);
        }
        tid = tid->next;
    }
}
