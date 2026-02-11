get_auth_header(request_rec * r, ntlm_config_rec * crec, const char *auth_scheme)
{
    const char *auth_line = apr_table_get(r->headers_in,
                                          (PROXYREQ_PROXY == r->proxyreq) ? "Proxy-Authorization"
                                          : "Authorization");

    if (!auth_line) {
        RERROR( APR_EINIT, "no auth line present" );
        return NULL;
    }
    if (strcmp(ap_getword_white(r->pool, &auth_line), auth_scheme)) {
        RERROR( APR_EINIT, "%s auth name not present", auth_scheme );
        return NULL;
    }
    return auth_line;
}
