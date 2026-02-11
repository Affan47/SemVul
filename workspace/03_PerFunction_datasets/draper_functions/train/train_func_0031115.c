request_pre_handler(REQUEST *request, UNUSED int action)
{
	TRACE_STATE_MACHINE;

	int rcode;

	if (request->master_state == REQUEST_STOP_PROCESSING) return 0;


	if (request->packet->dst_port == 0) {
		request->username = pairfind(request->packet->vps,
					     PW_USER_NAME, 0);
		request->password = pairfind(request->packet->vps,
					     PW_USER_PASSWORD, 0);
		return 1;
	}

#ifdef WITH_PROXY


	if (request->proxy_reply != NULL) {
		rcode = request->proxy_listener->decode(request->proxy_listener, request);
		DEBUG_PACKET(request, request->proxy_reply, 0);


		if ((rcode == 0) &&
		    (request->num_proxied_requests <= request->num_proxied_responses)) {
			remove_from_proxy_hash(request);
		}

	} else
#endif
	if (request->packet->vps == NULL) {
		rcode = request->listener->decode(request->listener, request);

#ifdef WITH_UNLANG
		if (debug_condition) {
			int result = FALSE;
			const char *my_debug = debug_condition;


			radius_evaluate_condition(request, RLM_MODULE_OK, 0,
						  &my_debug, 1,
						  &result);
			if (result) {
				request->options = 2;
				request->radlog = radlog_request;
			}
		}
#endif

		DEBUG_PACKET(request, request->packet, 0);
	} else {
		rcode = 0;
	}

	if (rcode < 0) {
		RDEBUG("Dropping packet without response because of error %s", fr_strerror());
		request->reply->offset = -2;
		return 0;
	}

	if (!request->username) {
		request->username = pairfind(request->packet->vps,
					     PW_USER_NAME, 0);
	}

#ifdef WITH_PROXY
	if (action == FR_ACTION_PROXY_REPLY) {
		return process_proxy_reply(request);
	}
#endif

	return 1;
}
