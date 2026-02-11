evhttp_connection_cb_cleanup(struct evhttp_connection *evcon)
{
	struct evcon_requestq requests;

	if (evcon->retry_max < 0 || evcon->retry_cnt < evcon->retry_max) {
		evtimer_assign(&evcon->retry_ev, evcon->base, evhttp_connection_retry, evcon);

		evhttp_add_event(&evcon->retry_ev,
		    MIN(3600, 2 << evcon->retry_cnt),
		    HTTP_CONNECT_TIMEOUT);
		evcon->retry_cnt++;
		return;
	}
	evhttp_connection_reset(evcon);


	TAILQ_INIT(&requests);
	while (TAILQ_FIRST(&evcon->requests) != NULL) {
		struct evhttp_request *request = TAILQ_FIRST(&evcon->requests);
		TAILQ_REMOVE(&evcon->requests, request, next);
		TAILQ_INSERT_TAIL(&requests, request, next);
	}


	while (TAILQ_FIRST(&requests) != NULL) {
		struct evhttp_request *request = TAILQ_FIRST(&requests);
		TAILQ_REMOVE(&requests, request, next);
		request->evcon = NULL;


		request->cb(request, request->cb_arg);
		evhttp_request_free(request);
	}
}
