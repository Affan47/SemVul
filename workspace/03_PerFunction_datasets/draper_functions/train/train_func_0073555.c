am_cache_new(server_rec *s, const char *key)
{
    am_cache_entry_t *t;
    am_mod_cfg_rec *mod_cfg;
    am_cache_entry_t *table;
    apr_time_t current_time;
    int i;
    apr_time_t age;
    int rv;
    char buffer[512];


    if(key == NULL || strlen(key) != AM_ID_LENGTH) {
        return NULL;
    }


    mod_cfg = am_get_mod_cfg(s);


    if((rv = apr_global_mutex_lock(mod_cfg->lock)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "apr_global_mutex_lock() failed [%d]: %s",
                     rv, apr_strerror(rv, buffer, sizeof(buffer)));
        return NULL;
    }

    table = apr_shm_baseaddr_get(mod_cfg->cache);


    current_time = apr_time_now();


    t = &table[0];


    for(i = 0; i < mod_cfg->init_cache_size; i++) {
        if(table[i].key[0] == '\0') {


            t = &table[i];
            break;
        }

        if(table[i].expires <= current_time) {


            t = &table[i];
            break;
        }

        if(table[i].access < t->access) {

            t = &table[i];
        }
    }


    if(t->key[0] != '\0' && t->expires > current_time) {

        age = (current_time - t->access) / 1000000;

        if(age < 3600) {
            ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s,
                         "Dropping LRU entry entry with age = %" APR_TIME_T_FMT
                         "s, which is less than one hour. It may be a good"
                         " idea to increase MellonCacheSize.",
                         age);
        }
    }


    strcpy(t->key, key);


    t->expires = 0x7fffffffffffffffLL;

    t->logged_in = 0;
    t->size = 0;
    t->user[0] = '\0';

    t->lasso_identity[0] = '\0';
    t->lasso_session[0] = '\0';

    return t;
}
