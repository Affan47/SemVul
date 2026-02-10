ap_proxyerror(request_rec *r, int statuscode, const char *message)
{
    const char *uri = ap_escape_html(r->pool, r->uri);
    apr_table_setn(r->notes, "error-notes",
        apr_pstrcat(r->pool,
            "The proxy server could not handle the request <em><a href=\"",
            uri, "\">", ap_escape_html(r->pool, r->method), "&nbsp;", uri,
            "</a></em>.<p>\n"
            "Reason: <strong>", ap_escape_html(r->pool, message),
            "</strong></p>",
            NULL));


    apr_table_setn(r->notes, "verbose-error-to", "*");

    r->status_line = apr_psprintf(r->pool, "%3.3u Proxy Error", statuscode);
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00898) "%s returned by %s", message,
                  r->uri);
    return statuscode;
}
