proxy_get_host_of_request(request_rec *r)
{
    char *url, *user = NULL, *password = NULL, *err, *host = NULL;
    apr_port_t port;

    if (r->hostname != NULL) {
        return r->hostname;
    }


    if ((url = strchr(r->uri, ':')) == NULL || url[1] != '/' || url[2] != '/') {
        return NULL;
    }

    url = apr_pstrdup(r->pool, &url[1]);

    err = ap_proxy_canon_netloc(r->pool, &url, &user, &password, &host, &port);

    if (err != NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00899) "%s", err);
    }

    r->hostname = host;

    return host;
}
