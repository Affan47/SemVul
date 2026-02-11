init_config_log(apr_pool_t *pc, apr_pool_t *p, apr_pool_t *pt, server_rec *s)
{
    int res;


    if (buffered_logs) {
        all_buffered_logs = apr_array_make(p, 5, sizeof(buffered_log *));
    }


    res = open_multi_logs(s, p);


    for (s = s->next; (res == OK) && s; s = s->next) {
        res = open_multi_logs(s, p);
    }

    return res;
}
