upload_progress_child_init(apr_pool_t *p, server_rec *s)
{
up_log(APLOG_MARK, APLOG_DEBUG, 0, s, "upload_progress_child_init()");

    apr_status_t rv;
    ServerConfig *config = get_server_config(s);

    if (!config->cache_lock) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, "Global mutex not set.");
        return;
    }

    rv = apr_global_mutex_child_init(&config->cache_lock, config->lock_file, p);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                     "Failed to initialise global mutex %s in child process %"
                     APR_PID_T_FMT ".", config->lock_file, getpid());
    }

    if (!config->cache_shm) {
        rv = apr_shm_attach(&config->cache_shm, config->cache_file, p);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, "Failed to attach to "
                         "shared memory file '%s'", config->cache_file);
            return;
        }
    }

    config->cache = (upload_progress_cache_t *)apr_shm_baseaddr_get(config->cache_shm);
    config->list = (int *)(config->cache + 1);
    config->nodes = (upload_progress_node_t *)(config->list + config->cache->count);
}
