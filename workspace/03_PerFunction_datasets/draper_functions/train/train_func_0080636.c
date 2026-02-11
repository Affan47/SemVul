do_invalid_pfind(const char *body, const char *failmsg)
{
    ne_request *req = ne_request_create(i_session, "PROPFIND", i_path);

    ne_set_request_body_buffer(req, body, strlen(body));

    ne_add_depth_header(req, NE_DEPTH_ZERO);

    ONV(ne_request_dispatch(req),
	("PROPFIND with %s failed: %s", failmsg, ne_get_error(i_session)));

    if (STATUS(400)) {
	t_context("PROPFIND with %s got %d response not 400",
		  failmsg, GETSTATUS);
	return FAIL;
    }

    ne_request_destroy(req);

    return OK;
}
