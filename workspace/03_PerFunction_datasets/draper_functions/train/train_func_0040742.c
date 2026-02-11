http_chunked_request_done(struct evhttp_request *req, void *arg)
{
	if (evhttp_request_get_response_code(req) != HTTP_OK) {
		fprintf(stderr, "FAILED\n");
		exit(1);
	}

	if (evhttp_find_header(evhttp_request_get_input_headers(req),
		"Transfer-Encoding") == NULL) {
		fprintf(stderr, "FAILED\n");
		exit(1);
	}

	if (evbuffer_get_length(evhttp_request_get_input_buffer(req)) != 13 + 18 + 8) {
		fprintf(stderr, "FAILED\n");
		exit(1);
	}

	if (strncmp((char *)evbuffer_pullup(evhttp_request_get_input_buffer(req), 13 + 18 + 8),
		"This is funnybut not hilarious.bwv 1052",
		13 + 18 + 8)) {
		fprintf(stderr, "FAILED\n");
		exit(1);
	}

	test_ok = 1;
	event_base_loopexit(arg, NULL);
}
