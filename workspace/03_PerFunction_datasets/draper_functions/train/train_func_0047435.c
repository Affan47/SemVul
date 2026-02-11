gnome_scan_plugin_params_remove (GnomeScanPlugin *plugin, GParamSpec *param)
{
	g_return_if_fail (GNOME_IS_SCAN_PLUGIN (plugin));
	g_param_spec_pool_remove (plugin->params, param);
	gnome_scan_plugin_params_changed (plugin, NULL);
}
