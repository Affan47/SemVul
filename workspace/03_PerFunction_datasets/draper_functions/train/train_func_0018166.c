validate(jk_worker_t *pThis,
                              jk_map_t *props,
                              jk_worker_env_t *we, jk_logger_t *l)
{
    jk_log(l, JK_LOG_DEBUG, "Into jk_worker_t::validate");

    if (pThis && pThis->worker_private) {
        ajp12_worker_t *p = pThis->worker_private;
        int port = jk_get_worker_port(props,
                                      p->name,
                                      AJP_DEF_PORT);

        const char *host = jk_get_worker_host(props,
                                        p->name,
                                        AJP_DEF_HOST);

        jk_log(l, JK_LOG_DEBUG,
               "In jk_worker_t::validate for worker %s contact is %s:%d",
               p->name, host, port);

        if (host) {
            if (jk_resolve(host, port, &p->worker_inet_addr, we->pool, l)) {
                return JK_TRUE;
            }
            jk_log(l, JK_LOG_ERROR,
                   "In jk_worker_t::validate, resolve failed");
        }
        jk_log(l, JK_LOG_ERROR, "In jk_worker_t::validate, Error %s %d",
               host, port);
    }
    else {
        jk_log(l, JK_LOG_ERROR,
               "In jk_worker_t::validate, NULL parameters");
    }

    return JK_FALSE;
}
