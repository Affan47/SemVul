handle_maxqueue(struct httpsqs* h, struct evhttp_request *req, struct sqs_queue_status *qs, struct evkeyvalq *args) {
	qs->total_info++;
	evhttp_add_header(req->output_headers, "Content-Type", "application/json");

	const char *input_maxqueue = evhttp_find_header(args, "num");
	int maxqueue = input_maxqueue == NULL ? 0 : atoi(input_maxqueue);
	if ( maxqueue != 0 && httpsqs_maxqueue(qs, maxqueue) != 0) {
		handle_status(h, req, qs, args);
		return;
	}

	send_error(req, 400, "Internal Server Error", "New maxqueue too small or invalid");
}
