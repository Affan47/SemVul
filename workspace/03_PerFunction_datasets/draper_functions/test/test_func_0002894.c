request_finished(struct evdns_request *const req, struct evdns_request **head) {
	struct evdns_base *base = req->base;
	int was_inflight = (head != &base->req_waiting_head);
	EVDNS_LOCK(base);
	if (head)
		evdns_request_remove(req, head);

	log(EVDNS_LOG_DEBUG, "Removing timeout for request %lx",
	    (unsigned long) req);
	search_request_finished(req);
	if (was_inflight) {
		evtimer_del(&req->timeout_event);
		base->global_requests_inflight--;
	} else {
		base->global_requests_waiting--;
	}

	if (!req->request_appended) {

		mm_free(req->request);
	} else {


	}

	mm_free(req);

	evdns_requests_pump_waiting_queue(base);
	EVDNS_UNLOCK(base);
}
