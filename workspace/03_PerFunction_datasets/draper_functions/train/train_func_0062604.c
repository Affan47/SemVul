ne_post(ne_session *sess, const char *uri, int fd, const char *buffer)
{
    ne_request *req = ne_request_create(sess, "POST", uri);
    int ret;

    ne_set_request_body_buffer(req, buffer, strlen(buffer));

    ret = dispatch_to_fd(req, fd, NULL);

    if (ret == NE_OK && ne_get_status(req)->klass != 2) {
	ret = NE_ERROR;
    }

    ne_request_destroy(req);

    return ret;
}
