midgard_connection_private_new (void)
{
	MidgardConnectionPrivate *cnc_private =
		g_new(MidgardConnectionPrivate, 1);

	cnc_private->pattern = NULL;
	cnc_private->config = NULL;
	cnc_private->copy_config = NULL;
	cnc_private->connected = FALSE;
	cnc_private->loghandler = 0;
	cnc_private->loglevel = 0;
	cnc_private->user = NULL;
	cnc_private->inherited = FALSE;
	cnc_private->parser = NULL;
	cnc_private->connection = NULL;
	cnc_private->configname = NULL;
	cnc_private->cnc_str = NULL;

	cnc_private->error_clbk_connected = FALSE;
	cnc_private->authtypes = NULL;
	cnc_private->authstack = NULL;


	cnc_private->timer = g_timer_new();
	g_timer_start(cnc_private->timer);

	cnc_private->enable_replication = FALSE;
	cnc_private->enable_quota = FALSE;
	cnc_private->enable_debug = FALSE;
	cnc_private->enable_dbus = FALSE;
	cnc_private->enable_workspace = FALSE;


	cnc_private->has_workspace = FALSE;
	cnc_private->workspace_model = NULL;
	cnc_private->workspace = NULL;
	cnc_private->workspace_manager = NULL;

	return cnc_private;
}
