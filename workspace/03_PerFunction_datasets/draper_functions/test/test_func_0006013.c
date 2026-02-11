rpc_basic_test(void)
{
	short port;
	struct evhttp *http = NULL;
	struct evrpc_base *base = NULL;
	struct evhttp_connection *evcon = NULL;
	struct evhttp_request *req = NULL;

	fprintf(stdout, "Testing Basic RPC Support: ");

	rpc_setup(&http, &port, &base);

	evcon = evhttp_connection_new("127.0.0.1", port);
	if (evcon == NULL) {
		fprintf(stdout, "FAILED\n");
		exit(1);
	}


	req = evhttp_request_new(rpc_postrequest_failure, NULL);
	if (req == NULL) {
		fprintf(stdout, "FAILED\n");
		exit(1);
	}


	evhttp_add_header(req->output_headers, "Host", "somehost");
	evbuffer_add_printf(req->output_buffer, "Some Nonsense");

	if (evhttp_make_request(evcon, req,
		EVHTTP_REQ_POST,
		"/.rpc.Message") == -1) {
		fprintf(stdout, "FAILED\n");
		exit(1);
	}

	test_ok = 0;

	event_dispatch();

	evhttp_connection_free(evcon);

	rpc_teardown(base);

	if (test_ok != 1) {
		fprintf(stdout, "FAILED\n");
		exit(1);
	}

	fprintf(stdout, "OK\n");

	evhttp_free(http);
}
