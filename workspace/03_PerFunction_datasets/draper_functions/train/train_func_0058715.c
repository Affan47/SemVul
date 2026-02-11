del_routes(struct vpn_provider *provider)
{
	GHashTableIter hash;
	gpointer value, key;

	g_hash_table_iter_init(&hash, provider->user_routes);
	while (handle_routes == TRUE && g_hash_table_iter_next(&hash,
						&key, &value) == TRUE) {
		struct vpn_route *route = value;
		if (route->family == AF_INET6) {
			unsigned char prefixlen = atoi(route->netmask);
			connman_inet_del_ipv6_network_route(provider->index,
							route->network,
							prefixlen);
		} else
			connman_inet_del_host_route(provider->index,
						route->network);
	}

	g_hash_table_remove_all(provider->user_routes);
	g_slist_free_full(provider->user_networks, free_route);
	provider->user_networks = NULL;
}
