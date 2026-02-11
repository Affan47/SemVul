http_sent_cb(struct evhttp_request *req, void *arg)
{
	ev_uintptr_t val = (ev_uintptr_t)arg;
	struct evbuffer *b;

	if (val != 0xDEADBEEF) {
		fprintf(stdout, "FAILED on_complete_cb argument\n");
		exit(1);
	}

	b = evhttp_request_get_output_buffer(req);
	if (evbuffer_get_length(b) != 0) {
		fprintf(stdout, "FAILED on_complete_cb output buffer not written\n");
		exit(1);
	}

	event_debug(("%s: called\n", __func__));

	++test_ok;
}
