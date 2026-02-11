sysThreadEnumerateOver(int (*func)(sys_thread_t *, void *), void *arg)
{
    sys_thread_t *tid;
    int err = SYS_OK;
    int i;

    sysAssert(SYS_QUEUE_LOCKED(sysThreadSelf()));

    tid = ThreadQueue;
    for (i = 0; i < ActiveThreadCount && tid != 0; i++) {
        if ((err = (*func)(tid, arg)) != SYS_OK) {
            break;
        }
        tid = tid->next;
    }

    return err;
}
