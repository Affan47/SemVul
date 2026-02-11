test_case_2(void)
{
	struct connman_ippool *pool;
	const char *gateway;
	const char *broadcast;
	const char *subnet_mask;
	const char *start_ip;
	const char *end_ip;
	int i;

	__connman_ippool_init();


	for (i = 1; i < 254; i++) {
		pool = __connman_ippool_create(23, 1, i, NULL, NULL);
		g_assert(pool);

		gateway = __connman_ippool_get_gateway(pool);
		broadcast = __connman_ippool_get_broadcast(pool);
		subnet_mask = __connman_ippool_get_subnet_mask(pool);
		start_ip = __connman_ippool_get_start_ip(pool);
		end_ip = __connman_ippool_get_end_ip(pool);

		g_assert(gateway);
		g_assert(broadcast);
		g_assert(subnet_mask);
		g_assert(start_ip);
		g_assert(end_ip);

		LOG("\n\tIP range %s --> %s\n"
			"\tgateway %s broadcast %s mask %s", start_ip, end_ip,
			gateway, broadcast, subnet_mask);

		__connman_ippool_unref(pool);
	}

	__connman_ippool_cleanup();
}
