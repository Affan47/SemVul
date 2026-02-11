fill_threadinfo(pthread_t id, const char *name,
                            gwthread_func_t *func,
                            struct threadinfo *ti)
{
    int pipefds[2];
    long first_try;

    gw_assert(active_threads < THREADTABLE_SIZE);


    ti->self = id;
    ti->name = name;
    ti->func = func;
    ti->pid = -1;
    ti->wakefd_recv = -1;
    ti->wakefd_send = -1;
    ti->joiners = NULL;
    ti->number = -1;

    if (pipe(pipefds) < 0) {
        error(errno, "cannot allocate wakeup pipe for new thread");
        return -1;
    }
    ti->wakefd_recv = pipefds[0];
    ti->wakefd_send = pipefds[1];
    socket_set_blocking(ti->wakefd_recv, 0);
    socket_set_blocking(ti->wakefd_send, 0);


    first_try = next_threadnumber;
    do {
        ti->number = next_threadnumber++;

        if (ti->number == first_try + THREADTABLE_SIZE) {
            error(0, "Cannot have more than %d active threads", THREADTABLE_SIZE);
            ti->number = -1;
            return -1;
        }
    } while (THREAD(ti->number) != NULL);
    THREAD(ti->number) = ti;

    active_threads++;

    return ti->number;
}
