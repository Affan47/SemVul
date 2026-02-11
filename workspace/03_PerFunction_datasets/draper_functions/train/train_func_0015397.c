isns_scn_transmit_all(void)
{
	time_t		now = time(NULL), next_timeout;
	isns_scn_t	*scn;

	for (scn = isns_scn_list; scn; scn = scn->scn_next) {
		isns_simple_t	*call;
		isns_socket_t	*sock;


		if ((call = scn->scn_pending) != NULL) {
			if (scn->scn_timeout > now)
				continue;
			scn->scn_current_funnel->scn_bad++;
			if (--(scn->scn_retries))
				goto retry;
			isns_warning("SCN for %s timed out\n",
					scn->scn_name);
			isns_simple_free(call);
			scn->scn_pending = NULL;
		}

		if ((call = scn->scn_message) == NULL)
			continue;

		isns_debug_scn("SCN: transmit pending message for %s\n",
				scn->scn_name);
		scn->scn_retries = isns_config.ic_scn_retries;
		scn->scn_pending = call;
		scn->scn_message = NULL;

retry:
		if ((sock = isns_scn_get_socket(scn)) == NULL) {

			isns_warning("SCN for %s dropped - no portal\n",
					scn->scn_name);
			scn->scn_pending = NULL;
			isns_simple_free(call);
			continue;
		}

		isns_simple_transmit(sock, call, NULL,
				isns_config.ic_scn_timeout,
				isns_process_scn_response);
		scn->scn_xid = call->is_xid;
		scn->scn_timeout = now + isns_config.ic_scn_timeout;
	}

	next_timeout = now + 3600;
	for (scn = isns_scn_list; scn; scn = scn->scn_next) {
		if (scn->scn_pending && scn->scn_timeout < next_timeout)
			next_timeout = scn->scn_timeout;
	}

	return next_timeout;
}
