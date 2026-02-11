uri_worker_map_update(jk_uri_worker_map_t *uw_map,
                          int force, jk_logger_t *l)
{
    int rc = JK_TRUE;
    time_t now = time(NULL);

    if (force || (uw_map->reload > 0 && difftime(now, uw_map->checked) >
                  uw_map->reload)) {
        struct stat statbuf;
        uw_map->checked = now;
        if ((rc = jk_stat(uw_map->fname, &statbuf)) == -1) {
            jk_log(l, JK_LOG_ERROR,
                   "Unable to stat the %s (errno=%d)",
                   uw_map->fname, errno);
            return JK_FALSE;
        }
        if (statbuf.st_mtime == uw_map->modified) {
            if (JK_IS_DEBUG_LEVEL(l))
                jk_log(l, JK_LOG_DEBUG,
                       "File %s is not modified",
                       uw_map->fname);
            return JK_TRUE;
        }
        JK_ENTER_CS(&uw_map->cs);

        if (statbuf.st_mtime == uw_map->modified) {
            JK_LEAVE_CS(&uw_map->cs);
            if (JK_IS_DEBUG_LEVEL(l))
                jk_log(l, JK_LOG_DEBUG,
                       "File %s  is not modified",
                       uw_map->fname);
            return JK_TRUE;
        }
        rc = uri_worker_map_load(uw_map, l);
        uri_worker_map_ext(uw_map, l);
        uri_worker_map_switch(uw_map, l);
        JK_LEAVE_CS(&uw_map->cs);
        jk_log(l, JK_LOG_INFO,
               "Reloaded urimaps from %s", uw_map->fname);
    }
    return JK_TRUE;
}
