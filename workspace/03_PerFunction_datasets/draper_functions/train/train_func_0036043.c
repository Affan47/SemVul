mgt_cli_telnet(const char *T_arg)
{
	struct vss_addr **ta;
	int i, n, sock, good;
	struct telnet *tn;
	struct vsb *vsb;
	char abuf[VTCP_ADDRBUFSIZE];
	char pbuf[VTCP_PORTBUFSIZE];

	n = VSS_resolve(T_arg, NULL, &ta);
	if (n == 0) {
		REPORT(LOG_ERR, "-T %s Could not be resolved\n", T_arg);
		exit(2);
	}
	good = 0;
	vsb = VSB_new_auto();
	XXXAN(vsb);
	for (i = 0; i < n; ++i) {
		sock = VSS_listen(ta[i], 10);
		if (sock < 0)
			continue;
		VTCP_myname(sock, abuf, sizeof abuf, pbuf, sizeof pbuf);
		VSB_printf(vsb, "%s %s\n", abuf, pbuf);
		good++;
		tn = telnet_new(sock);
		tn->ev = vev_new();
		XXXAN(tn->ev);
		tn->ev->fd = sock;
		tn->ev->fd_flags = POLLIN;
		tn->ev->callback = telnet_accept;
		AZ(vev_add(mgt_evb, tn->ev));
		free(ta[i]);
		ta[i] = NULL;
	}
	free(ta);
	if (good == 0) {
		REPORT(LOG_ERR, "-T %s could not be listened on.", T_arg);
		exit(2);
	}
	AZ(VSB_finish(vsb));

	mgt_SHM_static_alloc(VSB_data(vsb), VSB_len(vsb) + 1, "Arg", "-T", "");
	VSB_delete(vsb);
}
