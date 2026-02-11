debug_dump_uri(request_rec *r)
{
    apr_uri_t *uri = &r->parsed_uri;
    if (uri)
        ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, "Dumping uri info "
                      "scheme='%s' host='%s' path='%s' query='%s' fragment='%s'",
                      uri->scheme, uri->hostname, uri->path, uri->query,
                      uri->fragment);
    else
        ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, "Asked to dump NULL uri");

}
