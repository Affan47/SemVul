scgi_handler(request_rec *r)
{
    apr_status_t rv = 0;
    int http_status = 0;
    struct sockbuff s;
    apr_socket_t *sock;
    apr_bucket_brigade *bb = NULL;
    apr_bucket *b          = NULL;
    const char *location;

    if (strcmp(r->handler, "scgi-handler"))
        return DECLINED;

    http_status = ap_setup_client_block(r, REQUEST_CHUNKED_ERROR);
    if (http_status != OK)
        return http_status;

    log_debug(APLOG_MARK, r, "connecting to server");

    rv = open_socket(&sock, r);
    if (rv) {
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    binit(&s, sock);

    rv = send_headers(r, &s);
    if (rv) {
        log_err(APLOG_MARK, r, rv, "error sending request headers");
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    rv = send_request_body(r, &s);
    if (rv) {
        log_err(APLOG_MARK, r, rv, "error sending request body");
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    rv = bflush(&s);
    if (rv) {
        log_err(APLOG_MARK, r, rv, "error sending request");
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    log_debug(APLOG_MARK, r, "reading response headers");
    bb = apr_brigade_create(r->connection->pool, r->connection->bucket_alloc);
    b = apr_bucket_socket_create(sock, r->connection->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, b);
    b = apr_bucket_eos_create(r->connection->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, b);

    rv = ap_scan_script_header_err_brigade(r, bb, NULL);
    if (rv) {
        if (rv == HTTP_INTERNAL_SERVER_ERROR) {
            log_err(APLOG_MARK, r, rv, "error reading response headers");
        }
        else {


            r->status_line = NULL;
        }
        apr_brigade_destroy(bb);
        return rv;
    }

    location = apr_table_get(r->headers_out, "Location");

    if (location && location[0] == '/' &&
        ((r->status == HTTP_OK) || ap_is_HTTP_REDIRECT(r->status))) {

        apr_brigade_destroy(bb);


        r->status = HTTP_OK;


        r->method = apr_pstrdup(r->pool, "GET");
        r->method_number = M_GET;

        ap_internal_redirect_handler(location, r);
        return OK;
    }

    rv = ap_pass_brigade(r->output_filters, bb);
    if (rv) {
        log_err(APLOG_MARK, r, rv, "ap_pass_brigade()");
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    return OK;
}
