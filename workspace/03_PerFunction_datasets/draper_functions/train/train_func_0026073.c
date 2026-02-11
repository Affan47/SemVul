http_on_complete_cb(struct evhttp_request *req, void *arg)
{
	struct evbuffer *evb = evbuffer_new();

	evhttp_request_set_on_complete_cb(req, http_sent_cb, (void *)0xDEADBEEF);

	event_debug(("%s: called\n", __func__));
	evbuffer_add_printf(evb, BASIC_REQUEST_BODY);


	evhttp_send_reply(req, HTTP_OK, "Everything is fine", evb);

	evbuffer_free(evb);

	++test_ok;
}
