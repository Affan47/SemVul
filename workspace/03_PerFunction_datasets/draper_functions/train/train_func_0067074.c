__connman_resolver_init(connman_bool_t dnsproxy)
{
	int i;
	char **ns;

	DBG("dnsproxy %d", dnsproxy);

	if (dnsproxy == FALSE)
		return 0;

	if (__connman_dnsproxy_init() < 0) {

		return 0;
	}

	dnsproxy_enabled = TRUE;

	ns = connman_setting_get_string_list("FallbackNameservers");
	for (i = 0; ns != NULL && ns[i] != NULL; i += 1) {
		DBG("server %s", ns[i]);
		append_resolver(-1, NULL, ns[i], 0, RESOLVER_FLAG_PUBLIC);
	}

	return 0;
}
