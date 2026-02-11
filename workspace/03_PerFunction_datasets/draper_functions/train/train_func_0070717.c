guess_discovered_host(host_addr_t addr, uint16 port)
{
	if (hostiles_is_bad(addr) || !host_address_is_usable(addr))
		return;

	if (is_my_address_and_port(addr, port))
		return;

	hcache_add_caught(HOST_GUESS, addr, port, "GUESS pong");

	if (hash_list_length(link_cache) < GUESS_LINK_CACHE_SIZE) {
		gnet_host_t host;

		gnet_host_set(&host, addr, port);
		if (guess_can_recontact(&host)) {
			guess_add_link_cache(&host, 100);
		}
	}
}
