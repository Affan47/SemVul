http_stream_in_done(struct evhttp_request *req, void *arg)
{
	if (evbuffer_get_length(req->input_buffer) != 0) {
		fprintf(stderr, "FAILED\n");
		exit(1);
	}

	event_loopexit(NULL);
}
