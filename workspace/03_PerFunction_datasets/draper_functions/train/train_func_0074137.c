display_worker_ajp_conf_details(jk_ws_service_t *s,
                                            status_endpoint_t *p,
                                            ajp_worker_t *aw,
                                            int is_member,
                                            int type,
                                            jk_logger_t *l)
{
    char buf[32];

    JK_TRACE_ENTER(l);

    if (is_member)
        jk_printf(s, JK_STATUS_SHOW_MEMBER_CONF_ROW,
                  aw->name,
                  status_worker_type(type),
                  aw->host,
                  dump_ajp_addr(aw, buf),
                  aw->cache_timeout,
                  aw->connect_timeout,
                  aw->prepost_timeout,
                  aw->reply_timeout,
                  aw->retries,
                  aw->recovery_opts,
                  aw->max_packet_size);
    else
        jk_printf(s, JK_STATUS_SHOW_AJP_CONF_ROW,
                  status_worker_type(type),
                  aw->host,
                  dump_ajp_addr(aw, buf),
                  aw->cache_timeout,
                  aw->connect_timeout,
                  aw->prepost_timeout,
                  aw->reply_timeout,
                  aw->retries,
                  aw->recovery_opts,
                  aw->max_packet_size);
    JK_TRACE_EXIT(l);

}
