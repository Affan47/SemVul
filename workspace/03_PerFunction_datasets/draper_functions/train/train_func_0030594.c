test_invalid_escaped_domain_searches (const char *client)
{
	GHashTable *options;
	NMIP4Config *ip4_config;

	options = fill_table (generic_options, NULL);
	options = fill_table (invalid_escaped_searches_options, options);

	ip4_config = nm_dhcp_manager_test_ip4_options_to_config (client, "eth0", options, "rebind");
	ASSERT (ip4_config != NULL,
	        "dhcp-invalid-escaped-domain-searches", "failed to parse DHCP4 options");


	ASSERT (nm_ip4_config_get_num_searches (ip4_config) == 0,
	        "dhcp-invalid-escaped-domain-searches", "unexpected domain searches");

	g_hash_table_destroy (options);
}
