orte_wait_signal_callback(int fd, short event, void *arg)
{
    opal_event_t *signal = (opal_event_t*) arg;

    if (SIGCHLD != OPAL_EVENT_SIGNAL(signal)) return;

    OPAL_THREAD_LOCK(&mutex);
    do_waitall(0);
    OPAL_THREAD_UNLOCK(&mutex);
}
