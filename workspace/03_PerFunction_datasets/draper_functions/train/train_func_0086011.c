test_dhclient_invalid_classless_routes_1 (const char *client)
{
	GHashTable *options;
	NMIP4Config *ip4_config;
	const char *expected_route1_dest = "192.168.10.0";
	const char *expected_route1_gw = "192.168.1.1";
	static Option data[] = {

		{ "new_rfc3442_classless_static_routes", "24 192 168 10 192 168 1 1 45 10 17 66 41" },
		{ NULL, NULL }
	};

	options = fill_table (generic_options, NULL);
	options = fill_table (data, options);

	ip4_config = nm_dhcp_manager_test_ip4_options_to_config (client, "eth0", options, "rebind");
	ASSERT (ip4_config != NULL,
	        "dhcp-dhclient-classless-invalid-1", "failed to parse DHCP4 options");


	ASSERT (nm_ip4_config_get_num_routes (ip4_config) == 1,
	        "dhcp-dhclient-classless-invalid-1", "unexpected number of IP routes");

	ip4_test_route ("dhcp-dhclient-classless-invalid-1", ip4_config, 0,
	                expected_route1_dest, expected_route1_gw, 24);

	g_hash_table_destroy (options);
}
