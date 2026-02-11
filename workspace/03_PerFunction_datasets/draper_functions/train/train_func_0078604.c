ne_options(ne_session *sess, const char *uri, ne_server_capabilities *caps)
{
    ne_request *req = ne_request_create(sess, "OPTIONS", uri);
    int ret = ne_request_dispatch(req);
    const char *header = ne_get_response_header(req, "DAV");

    if (header) parse_dav_header(header, caps);

    if (ret == NE_OK && ne_get_status(req)->klass != 2) {
	ret = NE_ERROR;
    }

    ne_request_destroy(req);

    return ret;
}
