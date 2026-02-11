ad_http_is_keepalive_request(ad_conn_t *conn) {
    ad_http_t *http = (ad_http_t *) ad_conn_get_extra(conn);
    if (http->request.httpver == NULL) {
        return 0;
    }

    const char *connection = ad_http_get_request_header(conn, "Connection");
    if (!strcmp(http->request.httpver, HTTP_PROTOCOL_11)) {

        if (connection != NULL && !strcmp(connection, "close")) {
            return 0;
        }
        return 1;
    } else {

        if (connection != NULL
                && (!strcmp(connection, "Keep-Alive")
                        || !strcmp(connection, "TE"))) {
            return 1;
        }
        return 0;
    }
}
