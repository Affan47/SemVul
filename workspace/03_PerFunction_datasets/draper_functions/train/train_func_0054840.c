evdns_request_transmit(struct request *req) {
	int retcode = 0, r;

	ASSERT_LOCKED(req->base);
	ASSERT_VALID_REQUEST(req);


	req->transmit_me = 1;
	EVUTIL_ASSERT(req->trans_id != 0xffff);

	if (req->ns->choked) {


		return 1;
	}

	r = evdns_request_transmit_to(req, req->ns);
	switch (r) {
	case 1:

		req->ns->choked = 1;
		nameserver_write_waiting(req->ns, 1);
		return 1;
	case 2:

		retcode = 1;


	default:

		log(EVDNS_LOG_DEBUG,
		    "Setting timeout for request %p", req);
		if (evtimer_add(&req->timeout_event, &req->base->global_timeout) < 0) {
			log(EVDNS_LOG_WARN,
		      "Error from libevent when adding timer for request %p",
			    req);

		}
		req->tx_count++;
		req->transmit_me = 0;
		return retcode;
	}
}
