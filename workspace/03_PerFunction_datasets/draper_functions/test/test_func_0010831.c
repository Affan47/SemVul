uhc_init(void)
{
	uint i;

	g_return_if_fail(NULL == uhc_list);
	uhc_list = hash_list_new(uhc_hash, uhc_equal);

	for (i = 0; i < G_N_ELEMENTS(boot_hosts); i++) {
		const char *host, *ep, *uhc;
		uint16 port;

		uhc = boot_hosts[i].uhc;


		uhc_get_host_port(uhc, &host, &port);
		g_assert(NULL != host);
		g_assert(0 != port);

		ep = is_strprefix(uhc, host);
		g_assert(NULL != ep);
		g_assert(':' == ep[0]);

		uhc_list_add(uhc);
	}
}
