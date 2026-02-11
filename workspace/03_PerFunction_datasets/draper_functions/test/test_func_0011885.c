G_main_add_IPC_WaitConnection(int priority
,	IPC_WaitConnection* wch
,	IPC_Auth* auth_info
,	gboolean can_recurse
,	gboolean (*dispatch)(IPC_Channel* wch
,		gpointer        user_data)
,	gpointer userdata
,	GDestroyNotify notify)
{

	GWCSource* wcp;
	GSource * source = g_source_new(&G_WC_SourceFuncs,
					sizeof(GWCSource));

	wcp = (GWCSource*)source;

	wcp->magno = MAG_GWCSOURCE;
	wcp->maxdispatchdelayms = DEFAULT_MAXDELAY;
	wcp->maxdispatchms = DEFAULT_MAXDISPATCH;
	lc_store((wcp->detecttime), zero_longclock);
	wcp->udata = userdata;
	wcp->gpfd.fd = wch->ops->get_select_fd(wch);
	wcp->gpfd.events = DEF_EVENTS;
	wcp->gpfd.revents = 0;
	wcp->wch = wch;
	wcp->dnotify = notify;
	wcp->auth_info = auth_info;
	wcp->dispatch = dispatch;

	g_source_add_poll(source, &wcp->gpfd);

	g_source_set_priority(source, priority);

	g_source_set_can_recurse(source, can_recurse);

	wcp->gsourceid = g_source_attach(source, NULL);
	wcp->description = "IPC wait for connection";

	if (wcp->gsourceid == 0) {
		g_source_remove_poll(source, &wcp->gpfd);
		g_source_unref(source);
		source = NULL;
		wcp = NULL;
	}
	return wcp;
}
