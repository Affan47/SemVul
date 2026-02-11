plugin_service_function_group_func_ref_notify (GnmFunc *fn_def, int refcount)
{
	GOPluginService *service;

	service = gnm_func_get_user_data (fn_def);
	g_return_if_fail (IS_GNM_PLUGIN_SERVICE_FUNCTION_GROUP (service));
	if (refcount == 0) {
		go_plugin_use_unref (service->plugin);
	} else {
		go_plugin_use_ref (service->plugin);
	}
}
