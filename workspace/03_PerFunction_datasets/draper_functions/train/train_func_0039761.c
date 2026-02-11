evhttp_connection_cb_cleanup(struct evhttp_connection *evcon)
{
	struct evcon_requestq requests;

	if (evcon->retry_max < 0 || evcon->retry_cnt < evcon->retry_max) {
		struct timeval tv_retry = evcon->initial_retry_timeout;
		int i;
		evtimer_assign(&evcon->retry_ev, evcon->base, evhttp_connection_retry, evcon);

		for (i=0; i < evcon->retry_cnt; ++i) {
			tv_retry.tv_usec *= 2;
			if (tv_retry.tv_usec > 1000000) {
				tv_retry.tv_usec -= 1000000;
				tv_retry.tv_sec += 1;
			}
			tv_retry.tv_sec *= 2;
			if (tv_retry.tv_sec > 3600) {
				tv_retry.tv_sec = 3600;
				tv_retry.tv_usec = 0;
			}
		}
		event_add(&evcon->retry_ev, &tv_retry);
		evcon->retry_cnt++;
		return;
	}
	evhttp_connection_reset_(evcon);


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
