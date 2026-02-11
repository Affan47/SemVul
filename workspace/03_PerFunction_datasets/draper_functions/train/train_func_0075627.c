rail_plugin_process_connect(rdpSvcPlugin* plugin)
{
	railPlugin* rail_plugin = (railPlugin*)plugin;

	DEBUG_RAIL("rail_plugin_process_connect() called.");
	rail_core_on_channel_connected(rail_plugin->session);
}
