istgt_open_uctl_portal(ISTGT_Ptr istgt)
{
	int port;
	int sock;
	int i;

	ISTGT_TRACELOG(ISTGT_TRACE_DEBUG, "istgt_open_uctl_portal\n");
	for (i = 0; i < istgt->nuctl_portal; i++) {
		if (istgt->uctl_portal[i].sock < 0) {
			ISTGT_TRACELOG(ISTGT_TRACE_NET,
			    "open host %s, port %s, tag %d\n",
			    istgt->uctl_portal[i].host,
			    istgt->uctl_portal[i].port,
			    istgt->uctl_portal[i].tag);
			port = (int)strtol(istgt->uctl_portal[i].port, NULL, 0);
			sock = istgt_listen(istgt->uctl_portal[i].host, port);
			if (sock < 0) {
				ISTGT_ERRLOG("listen error %.64s:%d\n",
				    istgt->uctl_portal[i].host, port);
				return -1;
			}
			istgt->uctl_portal[i].sock = sock;
		}
	}
	return 0;
}
