node_init(void)
{
	time_t now = clock_loc2gmt(tm_time());

	STATIC_ASSERT(23 == sizeof(gnutella_header_t));

	no_metadata = deconstify_pointer(vmm_trap_page());
	rxbuf_init();
	proxies = pproxy_set_allocate(0);

	header_features_add_guarded(FEATURES_CONNECTIONS, "browse",
		BH_VERSION_MAJOR, BH_VERSION_MINOR,
		GNET_PROPERTY_PTR(browse_host_enabled));


	query_hashvec = qhvec_alloc(QRP_HVEC_MAX);

	unstable_servent   = htable_create(HASH_KEY_SELF, 0);
    ht_connected_nodes = htable_create_any(
							gnet_host_hash, gnet_host_hash2, gnet_host_eq);
	nodes_by_id        = hikset_create_any(
							offsetof(struct gnutella_node, id),
							nid_hash, nid_equal);
	nodes_by_guid      = hikset_create(
							offsetof(struct gnutella_node, guid),
							HASH_KEY_FIXED, GUID_RAW_SIZE);

	start_rfc822_date = atom_str_get(timestamp_rfc822_to_string(now));
	gnet_prop_set_timestamp_val(PROP_START_STAMP, now);

	udp_node = node_udp_create(NET_TYPE_IPV4);
	udp6_node = node_udp_create(NET_TYPE_IPV6);
	udp_sr_node = node_udp_sr_create(NET_TYPE_IPV4);
	udp6_sr_node = node_udp_sr_create(NET_TYPE_IPV6);
	dht_node = node_dht_create(NET_TYPE_IPV4);
	dht6_node = node_dht_create(NET_TYPE_IPV6);
	browse_node = node_browse_create();
	udp_route = node_udp_create(NET_TYPE_IPV4);

	payload_inflate_buffer_len = settings_max_msg_size();
	payload_inflate_buffer = halloc(payload_inflate_buffer_len);


	tcp_crawls = aging_make(TCP_CRAWLER_FREQ,
		host_addr_hash_func, host_addr_eq_func, wfree_host_addr);

	udp_crawls = aging_make(UDP_CRAWLER_FREQ,
		host_addr_hash_func, host_addr_eq_func, wfree_host_addr);


#define PAT_COMPILE(x)	pattern_compile_fast((x), CONST_STRLEN(x))

	pat_gtkg_23v1	= PAT_COMPILE(" GTKG/23v1");
	pat_hsep		= PAT_COMPILE(" HSEP/");
	pat_impp		= PAT_COMPILE(" IMPP/");
	pat_lmup		= PAT_COMPILE(" LMUP/");
	pat_f2ft_1		= PAT_COMPILE(" F2FT/1");

#undef PAT_COMPILE


	header_features_add(FEATURES_CONNECTIONS, "sflag", 0, 1);


	header_features_add_guarded_function(FEATURES_CONNECTIONS, "IP",
		INET_IP_V6READY, INET_IP_NOV4, settings_running_ipv6_only);
	header_features_add_guarded_function(FEATURES_CONNECTIONS, "IP",
		INET_IP_V6READY, INET_IP_V4V6, settings_running_ipv4_and_ipv6);

	cq_periodic_main_add(
		node_error_cleanup_timer * 1000, node_error_cleanup, NULL);
}
