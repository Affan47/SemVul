strip_webauth_info(MWA_REQ_CTXT *rc)
{
    char *c;
    size_t cookie_start, copy;
    char *d, *s;
    const char *mwa_func = "strip_webauth_cookies";

    c = (char*) apr_table_get(rc->r->headers_in, "Referer");
    if (c != NULL)
        strip_end(c, WEBAUTHR_MAGIC);

    c = (char*) apr_table_get(rc->r->headers_in, "Cookie");

    if (c == NULL || (ap_strstr(c, "webauth_") == NULL))
        return;

    if (rc->sconf->debug)
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, rc->r->server,
                     "mod_webauth: %s: need to strip: %s", mwa_func, c);
    s = d = c;
    cookie_start = copy = 1;
    while (*s) {
        if (cookie_start && *s != ' ') {
            copy = strncmp(s, "webauth_", 8) != 0;
            cookie_start = 0;
        } else if (*s == ';') {
            cookie_start = 1;
        }
        if (copy) {
            if (d != s)
                *d = *s;
            d++;
        }
        s++;
    }


    while (d > c && *(d-1) == ' ')
        d--;


    *d = '\0';

    if (*c == '\0') {
        apr_table_unset(rc->r->headers_in, "Cookie");
        if (rc->sconf->debug)
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, rc->r->server,
                         "mod_webauth: %s: no cookies after strip", mwa_func);
    } else {

        if (rc->sconf->debug)
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, rc->r->server,
                         "mod_webauth: %s: after strip: %s", mwa_func, c);
    }
}
