display_maps(jk_ws_service_t *s,
                         status_endpoint_t *p,
                         const char *worker,
                         jk_logger_t *l)
{
    int mime;
    unsigned int hide;
    int has_server_iterator = 0;
    int count=0;
    const char *arg;
    status_worker_t *w = p->worker;
    jk_uri_worker_map_t *uw_map;
    char server_name[80];
    void *srv;

    JK_TRACE_ENTER(l);
    status_get_string(p, JK_STATUS_ARG_MIME, NULL, &arg, l);
    mime = status_mime_int(arg);
    hide = status_get_int(p, JK_STATUS_ARG_OPTIONS, 0, l) &
                          JK_STATUS_ARG_OPTION_NO_MAPS;
    if (s->next_vhost)
        has_server_iterator = 1;

    count = count_maps(s, worker, l);

    if (hide) {
        if (count && mime == JK_STATUS_MIME_HTML) {
            jk_puts(s, "<p>\n");
            status_write_uri(s, p, "Show URI Mappings", JK_STATUS_CMD_UNKNOWN, JK_STATUS_MIME_UNKNOWN,
                             NULL, NULL, 0, JK_STATUS_ARG_OPTION_NO_MAPS, NULL, l);
            jk_puts(s, "</p>\n");
        }
        JK_TRACE_EXIT(l);
        return;
    }

    if (count) {
        if (mime == JK_STATUS_MIME_HTML) {
            jk_printf(s, "<hr/><h3>URI Mappings for %s (%d maps) [", worker, count);
            status_write_uri(s, p, "Hide", JK_STATUS_CMD_UNKNOWN, JK_STATUS_MIME_UNKNOWN,
                             NULL, NULL, JK_STATUS_ARG_OPTION_NO_MAPS, 0, NULL, l);
            jk_puts(s, "]</h3><table>\n");
            if (has_server_iterator)
                jk_printf(s, JK_STATUS_URI_MAP_TABLE_HEAD2,
                          "Server", "URI", "Match Type", "Source", "Reply Timeout", "Sticky Ignore", "Stateless", "Fail on Status", "Active", "Disabled", "Stopped", "Use Server Errors");
            else
                jk_printf(s, JK_STATUS_URI_MAP_TABLE_HEAD,
                          "URI", "Match Type", "Source", "Reply Timeout", "Sticky Ignore", "Stateless", "Fail on Status", "Active", "Disabled", "Stopped", "Use Server Errors");
        }
        count = 0;
        if (has_server_iterator) {
            for (srv = s->next_vhost(NULL); srv; srv = s->next_vhost(srv)) {
                uw_map = s->vhost_to_uw_map(srv);
                if (uw_map) {
                    s->vhost_to_text(srv, server_name, 80);
                    display_map(s, p, uw_map, worker, server_name, &count, mime, l);
                }
            }
        }
        else {
            uw_map = s->uw_map;
            if (uw_map) {
                display_map(s, p, uw_map, worker, NULL, &count, mime, l);
            }
        }
        if (mime == JK_STATUS_MIME_HTML) {
            jk_puts(s, "</table>\n");
        }
    }
    else {
        if (mime == JK_STATUS_MIME_HTML) {
            jk_putv(s, "<hr/><h3>Warning: No URI Mappings defined for ",
                    worker, " !</h3>\n", NULL);
        }
    }
    if (JK_IS_DEBUG_LEVEL(l))
        jk_log(l, JK_LOG_DEBUG,
               "Status worker '%s' displayed %d maps for worker '%s'",
               w->name, count, worker);
    JK_TRACE_EXIT(l);
}
