sync_init(void)
{
    int res;

    sync_queue = q_init();
    if (!sync_queue)
        return -1;

    pthread_mutex_lock(&m_sync_ht);


    ht_init(&sync_ht, sync_hash, sync_cmp);


    res = db_load_sync(sync_ht_set);

    pthread_mutex_unlock(&m_sync_ht);
    return res;
}
