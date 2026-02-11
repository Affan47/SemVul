xdmcp_new(char *config_path)
{
	XDMCPD *xdm = g_malloc(sizeof(XDMCPD));

	if (config_path)
		xdm->config_path = config_path;
	else
		xdm->config_path = g_strdup("xdmcpd.conf");
	xdmcp_configure(xdm);

	int s = open_sock();
	xdm->fd = s;
	bzero(&xdm->buf, sizeof(xdm->buf));
	xdm->sessions = NULL;
	xdm->acclist = NULL;

	char hostbuf[1024];
	gethostname(hostbuf, sizeof(hostbuf));
	struct utsname name;
	uname(&name);
	xdm->sysid = g_strconcat(name.sysname, " ", name.release, NULL);
	xdm->servhost.data = (CARD8 *)g_strdup(hostbuf);
	xdm->servhost.length = strlen((char *)xdm->servhost.data);

	xdm->ioc = g_io_channel_unix_new(s);
	g_io_channel_set_encoding(xdm->ioc, NULL, NULL);
	g_io_channel_set_buffered(xdm->ioc, FALSE);

	g_io_add_watch_full(xdm->ioc, G_PRIORITY_DEFAULT,
						G_IO_IN | G_IO_ERR | G_IO_HUP,
						(GIOFunc)decode_packet, xdm, NULL);
	g_io_channel_unref(xdm->ioc);

	g_timeout_add_seconds(CLEANUP_TIMEOUT, (GSourceFunc)xdmcp_cleanup_sessions, xdm);

	xdmcp_load_acclist(xdm);

	GFile *afile = g_file_new_for_path(xdm->acclist_path);
	GFileMonitor *mon = g_file_monitor_file(afile, G_FILE_MONITOR_NONE, NULL, NULL);
	g_warn_if_fail(mon != NULL);
	g_signal_connect(mon, "changed", G_CALLBACK(acclist_changed), xdm);
	xdm->amon = mon;
	g_object_unref(afile);

	return xdm;
}
