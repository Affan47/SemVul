init_turn_server(turn_turnserver* server,
		turnserver_id id, int verbose, ioa_engine_handle e,
		int stun_port, int fingerprint, dont_fragment_option_t dont_fragment,
		turn_credential_type ct,
		u08bits *realm,
		get_user_key_cb userkeycb,
		check_new_allocation_quota_cb chquotacb,
		release_allocation_quota_cb raqcb,
		ioa_addr *external_ip,
		vintp no_tcp_relay,
		vintp no_udp_relay,
		vintp stale_nonce,
		vintp stun_only,
		vintp no_stun,
		turn_server_addrs_list_t *alternate_servers_list,
		turn_server_addrs_list_t *tls_alternate_servers_list,
		turn_server_addrs_list_t *aux_servers_list,
		int self_udp_balance,
		vintp no_multicast_peers, vintp no_loopback_peers,
		ip_range_list_t* ip_whitelist, ip_range_list_t* ip_blacklist,
		send_socket_to_relay_cb send_socket_to_relay,
		vintp secure_stun, SHATYPE shatype, vintp mobility, int server_relay,
		send_turn_session_info_cb send_turn_session_info) {

	if (!server)
		return;

	ns_bzero(server,sizeof(turn_turnserver));

	server->e = e;
	server->id = id;
	server->ctime = turn_time();
	server->session_id_counter = 0;
	server->sessions_map = ur_map_create();
	server->tcp_relay_connections = ur_map_create();
	server->ct = ct;
	STRCPY(server->realm,realm);
	server->userkeycb = userkeycb;
	server->chquotacb = chquotacb;
	server->raqcb = raqcb;
	server->no_multicast_peers = no_multicast_peers;
	server->no_loopback_peers = no_loopback_peers;
	server->secure_stun = secure_stun;
	server->shatype = shatype;
	server->mobility = mobility;
	server->server_relay = server_relay;
	server->send_turn_session_info = send_turn_session_info;
	if(mobility)
		server->mobile_connections_map = ur_map_create();

	TURN_LOG_FUNC(TURN_LOG_LEVEL_INFO,"turn server id=%d created\n",(int)id);

	server->no_tcp_relay = no_tcp_relay;
	server->no_udp_relay = no_udp_relay;

	server->alternate_servers_list = alternate_servers_list;
	server->tls_alternate_servers_list = tls_alternate_servers_list;
	server->aux_servers_list = aux_servers_list;
	server->self_udp_balance = self_udp_balance;

	server->stale_nonce = stale_nonce;
	server->stun_only = stun_only;
	server->no_stun = no_stun;

	server->dont_fragment = dont_fragment;
	server->fingerprint = fingerprint;
	if(external_ip) {
		addr_cpy(&(server->external_ip), external_ip);
		server->external_ip_set = 1;
	}
	if (stun_port < 1)
		stun_port = DEFAULT_STUN_PORT;

	server->verbose = verbose;

	server->ip_whitelist = ip_whitelist;
	server->ip_blacklist = ip_blacklist;

	server->send_socket_to_relay = send_socket_to_relay;

	set_ioa_timer(server->e, 1, 0, timer_timeout_handler, server, 1, "timer_timeout_handler");
}
