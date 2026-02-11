failure_redirect(MWA_REQ_CTXT *rc)
{
    const char *redirect_url, *uri;
    const char *mwa_func="failure_redirect";

    ap_discard_request_body(rc->r);

    uri = rc->dconf->failure_url;

    if (uri == NULL) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, rc->r->server,
                     "mod_webauth: %s: no URL configured", mwa_func);
        set_pending_cookies(rc);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    if (uri[0] != '/') {
        redirect_url = uri;
    } else {
        redirect_url = ap_construct_url(rc->r->pool, uri, rc->r);
    }

    apr_table_setn(rc->r->err_headers_out, "Location", redirect_url);

    if (rc->sconf->debug)
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, rc->r->server,
                     "mod_webauth: %s: redirect(%s)", mwa_func, redirect_url);

    set_pending_cookies(rc);
    return do_redirect(rc);
}
