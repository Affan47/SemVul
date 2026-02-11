proxy_msrpc_disconnect_backend(void *data) {
    conn_rec *c = (conn_rec *)data;
    if (c == NULL)
        return APR_SUCCESS;

    msrpc_backend_t *d = (msrpc_backend_t *)ap_get_module_config(c->conn_config, &proxy_msrpc_module);
    if (d == NULL)
        return APR_SUCCESS;

    ap_set_module_config(c->conn_config, &proxy_msrpc_module, NULL);
    d->conn->close = 1;
    ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, d->server,
                  "%s: Client connection cleanup triggered release of backend connection 0x%pp back to pool",
                  d->proxy_function, d->conn);
    ap_proxy_release_connection(d->proxy_function, d->conn, d->server);
    return APR_SUCCESS;
}
