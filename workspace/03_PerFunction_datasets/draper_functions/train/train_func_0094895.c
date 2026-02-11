ap_proxy_connect_to_backend(apr_socket_t **newsock,
                                               const char *proxy_function,
                                               apr_sockaddr_t *backend_addr,
                                               const char *backend_name,
                                               proxy_server_conf *conf,
                                               request_rec *r)
{
    apr_status_t rv;
    int connected = 0;
    int loglevel;

    while (backend_addr && !connected) {
        if ((rv = apr_socket_create(newsock, backend_addr->family,
                                    SOCK_STREAM, 0, r->pool)) != APR_SUCCESS) {
            loglevel = backend_addr->next ? APLOG_DEBUG : APLOG_ERR;
            ap_log_rerror(APLOG_MARK, loglevel, rv, r, APLOGNO(00935)
                          "%s: error creating fam %d socket for target %s",
                          proxy_function, backend_addr->family, backend_name);


            backend_addr = backend_addr->next;
            continue;
        }

        if (conf->recv_buffer_size > 0 &&
            (rv = apr_socket_opt_set(*newsock, APR_SO_RCVBUF,
                                     conf->recv_buffer_size))) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(00936)
                          "apr_socket_opt_set(SO_RCVBUF): Failed to set "
                          "ProxyReceiveBufferSize, using default");
        }

        rv = apr_socket_opt_set(*newsock, APR_TCP_NODELAY, 1);
        if (rv != APR_SUCCESS && rv != APR_ENOTIMPL) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(00937)
                          "apr_socket_opt_set(APR_TCP_NODELAY): "
                          "Failed to set");
        }


        if (conf->timeout_set) {
            apr_socket_timeout_set(*newsock, conf->timeout);
        }
        else {
            apr_socket_timeout_set(*newsock, r->server->timeout);
        }

        ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                      "%s: fam %d socket created to connect to %s",
                      proxy_function, backend_addr->family, backend_name);

        if (conf->source_address) {
            rv = apr_socket_bind(*newsock, conf->source_address);
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(00938)
                              "%s: failed to bind socket to local address",
                              proxy_function);
            }
        }


        rv = apr_socket_connect(*newsock, backend_addr);


        if (rv != APR_SUCCESS) {
            apr_socket_close(*newsock);
            loglevel = backend_addr->next ? APLOG_DEBUG : APLOG_ERR;
            ap_log_rerror(APLOG_MARK, loglevel, rv, r, APLOGNO(00939)
                          "%s: attempt to connect to %pI (%s) failed",
                          proxy_function, backend_addr, backend_name);
            backend_addr = backend_addr->next;
            continue;
        }
        connected = 1;
    }
    return connected ? 0 : 1;
}
