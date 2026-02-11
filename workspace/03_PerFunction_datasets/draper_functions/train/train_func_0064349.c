output_headers(request_rec *r, AV *headers)
{
    dTHX;
    SV *key_sv, *val_sv;
    char *key;

    r->content_type = NULL;
    while (av_len(headers) > -1) {
        key_sv = av_shift(headers);
        val_sv = av_shift(headers);
        if (key_sv == NULL || val_sv == NULL) break;
        key = SvPV_nolen(key_sv);
        if (strcmp(key, "Content-Type") == 0) {
            r->content_type = apr_pstrdup(r->pool, SvPV_nolen(val_sv));
        } else if (strcmp(key, "Content-Length") == 0) {
            ap_set_content_length(r, SvIV(val_sv));
        } else if (strcmp(key, "Status") == 0) {
            server_error(r, "headers must not contain a Status");
            return HTTP_INTERNAL_SERVER_ERROR;
        } else {
            apr_table_add(r->headers_out, key, SvPV_nolen(val_sv));
        }
        SvREFCNT_dec(key_sv);
        SvREFCNT_dec(val_sv);
    }
    return OK;
}
