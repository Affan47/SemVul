uri_worker_map_open(jk_uri_worker_map_t *uw_map,
                        jk_map_t *init_data, jk_logger_t *l)
{
    int rc = JK_TRUE;

    JK_TRACE_ENTER(l);

    if (uw_map) {
        int sz = jk_map_size(init_data);

        if (JK_IS_DEBUG_LEVEL(l))
            jk_log(l, JK_LOG_DEBUG,
                   "rule map size is %d",
                   sz);

        if (sz > 0) {
            int i;
            for (i = 0; i < sz; i++) {
                const char *u = jk_map_name_at(init_data, i);
                const char *w = jk_map_value_at(init_data, i);


                if (strchr(u, '|')) {
                    char *s, *r = strdup(u);
                    s = strchr(r, '|');
                    *(s++) = '\0';

                    if (!uri_worker_map_add(uw_map, r, w, SOURCE_TYPE_JKMOUNT, l)) {
                        jk_log(l, JK_LOG_ERROR,
                        "invalid mapping rule %s->%s", r, w);
                        rc = JK_FALSE;
                    }
                    for (; *s; s++)
                        *(s - 1) = *s;
                    *(s - 1) = '\0';

                    if (!uri_worker_map_add(uw_map, r, w, SOURCE_TYPE_JKMOUNT, l)) {
                        jk_log(l, JK_LOG_ERROR,
                               "invalid mapping rule %s->%s", r, w);
                        rc = JK_FALSE;
                    }
                    free(r);
                }
                else if (!uri_worker_map_add(uw_map, u, w, SOURCE_TYPE_JKMOUNT, l)) {
                    jk_log(l, JK_LOG_ERROR,
                           "invalid mapping rule %s->%s",
                           u, w);
                    rc = JK_FALSE;
                    break;
                }
                if (rc == JK_FALSE)
                    break;
            }
        }

        if (rc == JK_FALSE) {
            jk_log(l, JK_LOG_ERROR,
                   "there was an error, freeing buf");
            jk_close_pool(&uw_map->p_dyn[0]);
            jk_close_pool(&uw_map->p_dyn[1]);
            jk_close_pool(&uw_map->p);
        }
        else if (JK_IS_DEBUG_LEVEL(l))
            uri_worker_map_dump(uw_map, "after map open", l);
    }

    JK_TRACE_EXIT(l);
    return rc;
}
