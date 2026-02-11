setup_listener(void)
{
	super_memory_t* sm = new_super_memory_region();

	turn_params.listener.tp = turnipports_create(sm, turn_params.min_port, turn_params.max_port);

	turn_params.listener.event_base = turn_event_base_new();

	TURN_LOG_FUNC(TURN_LOG_LEVEL_INFO,"IO method (main listener thread): %s\n",event_base_get_method(turn_params.listener.event_base));

	turn_params.listener.ioa_eng = create_ioa_engine(sm, turn_params.listener.event_base, turn_params.listener.tp, turn_params.relay_ifname, turn_params.relays_number, turn_params.relay_addrs, turn_params.default_relays, turn_params.verbose, turn_params.max_bps);

	if(!turn_params.listener.ioa_eng)
		exit(-1);

	set_ssl_ctx(turn_params.listener.ioa_eng, turn_params.tls_ctx_ssl23, turn_params.tls_ctx_v1_0,
#if defined(SSL_TXT_TLSV1_1)
					turn_params.tls_ctx_v1_1,
#if defined(SSL_TXT_TLSV1_2)
					turn_params.tls_ctx_v1_2,
#endif
#endif
					turn_params.dtls_ctx);

	turn_params.listener.rtcpmap = rtcp_map_create(turn_params.listener.ioa_eng);

#if !defined(TURN_NO_HIREDIS)
	if(turn_params.use_redis_statsdb) {
		turn_params.listener.rch = get_redis_async_connection(turn_params.listener.event_base, turn_params.redis_statsdb);
		set_default_async_context(turn_params.listener.rch);
		turn_report_allocation_delete_all();
	}
#endif

	ioa_engine_set_rtcp_map(turn_params.listener.ioa_eng, turn_params.listener.rtcpmap);

	{
		struct bufferevent *pair[2];

		bufferevent_pair_new(turn_params.listener.event_base, TURN_BUFFEREVENTS_OPTIONS, pair);
		turn_params.listener.in_buf = pair[0];
		turn_params.listener.out_buf = pair[1];
		bufferevent_setcb(turn_params.listener.in_buf, listener_receive_message, NULL, NULL, &turn_params.listener);
		bufferevent_enable(turn_params.listener.in_buf, EV_READ);
	}

	if(turn_params.listener.addrs_number<2 || turn_params.external_ip) {
		turn_params.rfc5780 = 0;
		TURN_LOG_FUNC(TURN_LOG_LEVEL_WARNING, "WARNING: I cannot support STUN CHANGE_REQUEST functionality because only one IP address is provided\n");
	} else {
		turn_params.listener.services_number = turn_params.listener.services_number * 2;
	}

	turn_params.listener.udp_services = (dtls_listener_relay_server_type***)allocate_super_memory_engine(turn_params.listener.ioa_eng, sizeof(dtls_listener_relay_server_type**)*turn_params.listener.services_number);
	turn_params.listener.dtls_services = (dtls_listener_relay_server_type***)allocate_super_memory_engine(turn_params.listener.ioa_eng, sizeof(dtls_listener_relay_server_type**)*turn_params.listener.services_number);

	turn_params.listener.aux_udp_services = (dtls_listener_relay_server_type***)allocate_super_memory_engine(turn_params.listener.ioa_eng, (sizeof(dtls_listener_relay_server_type**)*turn_params.aux_servers_list.size)+sizeof(void*));
}
