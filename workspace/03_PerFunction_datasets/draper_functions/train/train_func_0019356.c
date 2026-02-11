drdynvc_process_connect(rdpSvcPlugin* plugin)
{
	drdynvcPlugin* drdynvc = (drdynvcPlugin*)plugin;

	DEBUG_DVC("connecting");

	drdynvc->channel_mgr = dvcman_new(drdynvc);
	dvcman_load_plugin(drdynvc->channel_mgr, svc_plugin_get_data(plugin));
	dvcman_init(drdynvc->channel_mgr);
}
