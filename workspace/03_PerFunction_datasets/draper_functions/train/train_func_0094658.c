_jid_stop_single_cache(_jid_prep_cache_t *cache) {
    if (*cache == NULL)
	return;

    _jid_clean_single_cache(*cache, time(NULL));

    g_mutex_lock((*cache)->mutex);
    g_hash_table_destroy((*cache)->hashtable);
    g_mutex_free((*cache)->mutex);

    free(*cache);

    *cache = NULL;
}
