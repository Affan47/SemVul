go_plugin_loader_module_load_service_file_opener (GOPluginLoader *loader,
						  GOPluginService *service,
						  GOErrorInfo **ret_error)
{
	GOPluginLoaderModule *loader_module = GO_PLUGIN_LOADER_MODULE (loader);
	gchar *func_name_file_probe, *func_name_file_open;
	gpointer module_func_file_probe = NULL, module_func_file_open = NULL;

	g_return_if_fail (GO_IS_PLUGIN_SERVICE_FILE_OPENER (service));

	GO_INIT_RET_ERROR_INFO (ret_error);
	func_name_file_probe = make_function_name (service, "_file_probe");
	g_module_symbol (loader_module->handle, func_name_file_probe, &module_func_file_probe);
	func_name_file_open = make_function_name (service, "_file_open");
	g_module_symbol (loader_module->handle, func_name_file_open, &module_func_file_open);
	if (module_func_file_open != NULL) {
		GOPluginServiceFileOpenerCallbacks *cbs;
		ServiceLoaderDataFileOpener *loader_data;

		cbs = go_plugin_service_get_cbs (service);
		cbs->plugin_func_file_probe = go_plugin_loader_module_func_file_probe;
		cbs->plugin_func_file_open = go_plugin_loader_module_func_file_open;

		loader_data = g_new (ServiceLoaderDataFileOpener, 1);
		loader_data->module_func_file_probe = module_func_file_probe;
		loader_data->module_func_file_open = module_func_file_open;
		g_object_set_data_full (G_OBJECT (service),
					"loader_data", loader_data, g_free);
	} else {
		*ret_error = go_error_info_new_printf (
			_("Module file \"%s\" has invalid format."),
			loader_module->module_file_name);
		go_error_info_add_details (*ret_error, go_error_info_new_printf (
			_("File doesn't contain \"%s\" function."), func_name_file_open));
	}
	g_free (func_name_file_probe);
	g_free (func_name_file_open);
}
