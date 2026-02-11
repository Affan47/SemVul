ccf_listen_address(struct cli *cli, const char * const *av, void *priv)
{
	struct listen_sock *ls;
	char h[32], p[32];

	(void)cli;
	(void)av;
	(void)priv;


	while(!hack_ready)
		(void)usleep(100*1000);

	VTAILQ_FOREACH(ls, &heritage.socks, list) {
		if (ls->sock < 0)
			continue;
		VTCP_myname(ls->sock, h, sizeof h, p, sizeof p);
		VCLI_Out(cli, "%s %s\n", h, p);
	}
}
