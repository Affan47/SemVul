go_plugin_load_service (GOPlugin *plugin, GOPluginService *service, GOErrorInfo **ret_error)
{
	g_return_if_fail (GO_IS_PLUGIN (plugin));
	g_return_if_fail (service != NULL);

	GO_INIT_RET_ERROR_INFO (ret_error);
	go_plugin_load_base (plugin, ret_error);
	if (*ret_error != NULL) {
		return;
	}
	go_plugin_loader_load_service (plugin->loader, service, ret_error);
}
