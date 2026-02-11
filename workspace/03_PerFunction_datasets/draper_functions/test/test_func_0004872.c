ap_condition_if_range(request_rec *r,
        apr_table_t *headers)
{
    const char *if_range, *etag;

    if ((if_range = apr_table_get(r->headers_in, "If-Range"))
            && apr_table_get(r->headers_in, "Range")) {
        if (if_range[0] == '"') {

            if ((etag = apr_table_get(headers, "ETag"))
                    && !strcmp(if_range, etag)) {
                return AP_CONDITION_STRONG;
            }
            else {
                return AP_CONDITION_NOMATCH;
            }

        }
        else {
            apr_int64_t mtime;
            apr_int64_t rtime, reqtime;


            mtime = apr_time_sec(apr_date_parse_http(
                            apr_table_get(headers, "Last-Modified")));
            if (mtime == APR_DATE_BAD) {
                mtime = apr_time_sec(r->mtime ? r->mtime : apr_time_now());
            }

            reqtime = apr_time_sec(apr_date_parse_http(
                            apr_table_get(headers, "Date")));
            if (!reqtime) {
                reqtime = apr_time_sec(r->request_time);
            }

            rtime = apr_time_sec(apr_date_parse_http(if_range));

            if (rtime == mtime) {
                if (reqtime < mtime + 60) {

                    return AP_CONDITION_NOMATCH;
                }
                else {
                    return AP_CONDITION_STRONG;
                }
            }
            else {
                return AP_CONDITION_NOMATCH;
            }
        }
    }

    return AP_CONDITION_NONE;
}
