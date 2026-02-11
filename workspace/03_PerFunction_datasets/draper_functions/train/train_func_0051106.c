ap_cache_cacheable_headers_out(request_rec *r)
{
    apr_table_t *headers_out;

    headers_out = apr_table_overlay(r->pool, r->headers_out,
                                        r->err_headers_out);

    apr_table_clear(r->err_headers_out);

    headers_out = ap_cache_cacheable_headers(r->pool, headers_out,
                                                  r->server);

    cache_control_remove(r,
            cache_table_getm(r->pool, headers_out, "Cache-Control"),
            headers_out);

    if (!apr_table_get(headers_out, "Content-Type")
        && r->content_type) {
        const char *ctype = ap_make_content_type(r, r->content_type);
        if (ctype) {
            apr_table_setn(headers_out, "Content-Type", ctype);
        }
    }

    if (!apr_table_get(headers_out, "Content-Encoding")
        && r->content_encoding) {
        apr_table_setn(headers_out, "Content-Encoding",
                       r->content_encoding);
    }

    return headers_out;
}
