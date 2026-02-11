gwthread_join(long thread)
{
    struct threadinfo *threadinfo;
    pthread_cond_t exit_cond;
    int ret;

    gw_assert(thread >= 0);

    lock();
    threadinfo = THREAD(thread);
    if (threadinfo == NULL || threadinfo->number != thread) {

        unlock();
        return;
    }


    ret = pthread_cond_init(&exit_cond, NULL);
    if (ret != 0) {
        warning(ret, "gwthread_join: cannot create condition variable.");
        unlock();
        return;
    }

    if (!threadinfo->joiners)
        threadinfo->joiners = gwlist_create();
    gwlist_append(threadinfo->joiners, &exit_cond);


    ret = pthread_cond_wait(&exit_cond, &threadtable_lock);
    unlock();

    if (ret != 0)
        warning(ret, "gwthread_join: error in pthread_cond_wait");

    pthread_cond_destroy(&exit_cond);
}
