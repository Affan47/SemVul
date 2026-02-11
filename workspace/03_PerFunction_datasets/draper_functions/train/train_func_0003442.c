dav_lookup_uri(const char *uri,
                                              request_rec * r,
                                              int must_be_absolute)
{
    dav_lookup_result result = { 0 };
    const char *scheme;
    apr_port_t port;
    apr_uri_t comp;
    char *new_file;
    const char *domain;


    if (apr_uri_parse(r->pool, uri, &comp) != APR_SUCCESS) {
        result.err.status = HTTP_BAD_REQUEST;
        result.err.desc = "Invalid syntax in Destination URI.";
        return result;
    }


    if (comp.scheme == NULL && must_be_absolute) {
        result.err.status = HTTP_BAD_REQUEST;
        result.err.desc = "Destination URI must be an absolute URI.";
        return result;
    }


    if (comp.query != NULL || comp.fragment != NULL) {
        result.err.status = HTTP_BAD_REQUEST;
        result.err.desc =
            "Destination URI contains invalid components "
            "(a query or a fragment).";
        return result;
    }


    if (comp.scheme != NULL || comp.port != 0 || must_be_absolute)
    {

        scheme = r->parsed_uri.scheme;
        if (scheme == NULL)
            scheme = ap_http_scheme(r);


        if (comp.port == 0)
            comp.port = apr_uri_port_of_scheme(comp.scheme);


        port = r->connection->local_addr->port;
        if (strcasecmp(comp.scheme, scheme) != 0
#ifdef APACHE_PORT_HANDLING_IS_BUSTED
            || comp.port != port
#endif
            ) {
            result.err.status = HTTP_BAD_GATEWAY;
            result.err.desc = apr_psprintf(r->pool,
                                           "Destination URI refers to "
                                           "different scheme or port "
                                           "(%s://hostname:%d)" APR_EOL_STR
                                           "(want: %s://hostname:%d)",
                                           comp.scheme ? comp.scheme : scheme,
                                           comp.port ? comp.port : port,
                                           scheme, port);
            return result;
        }
    }


    if (comp.hostname != NULL
        && strrchr(comp.hostname, '.') == NULL
        && (domain = strchr(r->server->server_hostname, '.')) != NULL) {
        comp.hostname = apr_pstrcat(r->pool, comp.hostname, domain, NULL);
    }


#ifdef APACHE_PORT_HANDLING_IS_BUSTED
    if (comp.hostname != NULL &&
        !ap_matches_request_vhost(r, comp.hostname, port)) {
        result.err.status = HTTP_BAD_GATEWAY;
        result.err.desc = "Destination URI refers to a different server.";
        return result;
    }
#endif


    new_file = apr_uri_unparse(r->pool, &comp, APR_URI_UNP_OMITSITEPART);


    result.rnew = ap_sub_req_method_uri(r->method, new_file, r, NULL);

    return result;
}
