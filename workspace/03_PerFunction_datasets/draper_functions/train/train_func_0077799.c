refresh_relay_connection(turn_turnserver* server,
		ts_ur_super_session *ss, u32bits lifetime, int even_port,
		u64bits in_reservation_token, u64bits *out_reservation_token,
		int *err_code) {

	UNUSED_ARG(even_port);
	UNUSED_ARG(in_reservation_token);
	UNUSED_ARG(out_reservation_token);
	UNUSED_ARG(err_code);

	allocation* a = get_allocation_ss(ss);

	if (server && ss && is_allocation_valid(a)) {

		if (lifetime < 1) {
			set_allocation_valid(&(ss->alloc),0);
			lifetime = 1;
		}

		ioa_timer_handle ev = set_ioa_timer(server->e, lifetime, 0,
				client_ss_allocation_timeout_handler, ss, 0,
				"refresh_client_ss_allocation_timeout_handler");

		set_allocation_lifetime_ev(a, server->ctime + lifetime, ev);

		return 0;

	} else {
		return -1;
	}
}
