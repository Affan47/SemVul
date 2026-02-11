gnm_plugin_loader_module_load_service_function_group (GOPluginLoader  *loader,
						      GOPluginService *service,
						      GOErrorInfo **ret_error)
{
	GnmPluginLoaderModule *loader_module = GNM_PLUGIN_LOADER_MODULE (loader);
	gchar *fn_info_array_name;
	GnmFuncDescriptor *module_fn_info_array = NULL;

	g_return_if_fail (IS_GNM_PLUGIN_SERVICE_FUNCTION_GROUP (service));

	GO_INIT_RET_ERROR_INFO (ret_error);
	fn_info_array_name = g_strconcat (
		go_plugin_service_get_id (service), "_functions", NULL);
	g_module_symbol (loader_module->handle, fn_info_array_name, (gpointer) &module_fn_info_array);
	if (module_fn_info_array != NULL) {
		PluginServiceFunctionGroupCallbacks *cbs;
		ServiceLoaderDataFunctionGroup *loader_data;
		gint i;

		cbs = go_plugin_service_get_cbs (service);
		cbs->func_desc_load = &gnm_plugin_loader_module_func_desc_load;

		loader_data = g_new (ServiceLoaderDataFunctionGroup, 1);
		loader_data->module_fn_info_array = module_fn_info_array;
		loader_data->function_indices = g_hash_table_new (&g_str_hash, &g_str_equal);
		for (i = 0; module_fn_info_array[i].name != NULL; i++) {
			g_hash_table_insert (loader_data->function_indices,
			                     (gpointer) module_fn_info_array[i].name,
			                     GINT_TO_POINTER (i));
		}
		g_object_set_data_full (
			G_OBJECT (service), "loader_data", loader_data, function_group_loader_data_free);
	} else {
		*ret_error = go_error_info_new_printf (
		             _("Module file \"%s\" has invalid format."),
		             loader_module->module_file_name);
		go_error_info_add_details (*ret_error,
					go_error_info_new_printf (
					_("File doesn't contain \"%s\" array."),
					fn_info_array_name));
	}
	g_free (fn_info_array_name);
}
