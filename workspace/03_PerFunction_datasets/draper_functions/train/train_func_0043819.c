go_plugin_loader_load_service (GOPluginLoader *l, GOPluginService *s, GOErrorInfo **err)
{
	GOPluginLoaderClass *klass;
	void (*load_service_method) (GOPluginLoader *, GOPluginService *, GOErrorInfo **) = NULL;

	g_return_if_fail (GO_IS_PLUGIN_LOADER (l));
	g_return_if_fail (GO_IS_PLUGIN_SERVICE (s));
	g_return_if_fail (go_plugin_loader_is_base_loaded (l));

	GO_INIT_RET_ERROR_INFO (err);

	klass = PL_GET_CLASS (l);
	if (klass->service_load && (klass->service_load) (l, s, err))
		return;

	if (GO_IS_PLUGIN_SERVICE_FILE_OPENER (s)) {
		load_service_method = klass->load_service_file_opener;
	} else if (GO_IS_PLUGIN_SERVICE_FILE_SAVER (s)) {
		load_service_method = klass->load_service_file_saver;
	} else if (GO_IS_PLUGIN_SERVICE_PLUGIN_LOADER (s)) {
		load_service_method = klass->load_service_plugin_loader;
	} else if (GO_IS_PLUGIN_SERVICE_SIMPLE (s)) {
		load_service_method = NULL;
	} else {
		*err = go_error_info_new_printf (_("Service '%s' not supported by loader."),
			G_OBJECT_TYPE_NAME (s));
	}
	if (load_service_method != NULL)
		load_service_method (l, s, err);

	if (*err == NULL) {
		gpointer num_services = g_object_get_data (G_OBJECT (l), "num-services");
		g_object_set_data (G_OBJECT (l), "num-services",
		    GINT_TO_POINTER (GPOINTER_TO_INT (num_services) + 1));
	}
}
