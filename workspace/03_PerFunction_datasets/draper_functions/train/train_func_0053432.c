ap_condition_if_none_match(request_rec *r,
        apr_table_t *headers)
{
    const char *if_nonematch, *etag;

    if_nonematch = apr_table_get(r->headers_in, "If-None-Match");
    if (if_nonematch != NULL) {

        if (if_nonematch[0] == '*') {
            return AP_CONDITION_STRONG;
        }


        if (r->method_number == M_GET) {
            if ((etag = apr_table_get(headers, "ETag")) != NULL) {
                if (apr_table_get(r->headers_in, "Range")) {
                    if (ap_find_etag_strong(r->pool, if_nonematch, etag)) {
                        return AP_CONDITION_STRONG;
                    }
                }
                else {
                    if (ap_find_etag_weak(r->pool, if_nonematch, etag)) {
                        return AP_CONDITION_WEAK;
                    }
                }
            }
        }

        else if ((etag = apr_table_get(headers, "ETag")) != NULL
                && ap_find_etag_strong(r->pool, if_nonematch, etag)) {
            return AP_CONDITION_STRONG;
        }
        return AP_CONDITION_NOMATCH;
    }

    return AP_CONDITION_NONE;
}
