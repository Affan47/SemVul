check_ip6_address (NMSettingIP6Config *config, int idx, const char *address_str, int plen, const char *gateway_str)
{
	NMIP6Address *ip6 = nm_setting_ip6_config_get_address (config, idx);
	struct in6_addr address;
	struct in6_addr gateway;

	g_assert (inet_pton (AF_INET6, address_str, &address) == 1);
	g_assert (inet_pton (AF_INET6, gateway_str, &gateway) == 1);

	g_assert (ip6);
	g_assert (!memcmp (nm_ip6_address_get_address (ip6), &address, sizeof(address)));
	g_assert (nm_ip6_address_get_prefix (ip6) == plen);
	g_assert (!memcmp (nm_ip6_address_get_gateway (ip6), &gateway, sizeof(gateway)));
}
