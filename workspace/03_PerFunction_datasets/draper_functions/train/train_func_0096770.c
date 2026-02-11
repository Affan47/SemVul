alert_joiners(void)
{
    struct threadinfo *threadinfo;
    pthread_cond_t *joiner_cond;

    threadinfo = getthreadinfo();
    if (!threadinfo->joiners)
        return;
    while ((joiner_cond = gwlist_extract_first(threadinfo->joiners))) {
        pthread_cond_broadcast(joiner_cond);
    }
}
