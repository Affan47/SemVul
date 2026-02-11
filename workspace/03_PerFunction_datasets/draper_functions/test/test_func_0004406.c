plugin_service_function_group_activate (GOPluginService *service, GOErrorInfo **ret_error)
{
	PluginServiceFunctionGroup *sfg =
		GNM_PLUGIN_SERVICE_FUNCTION_GROUP (service);

	GO_INIT_RET_ERROR_INFO (ret_error);
	sfg->func_group = gnm_func_group_fetch (sfg->category_name,
						sfg->translated_category_name);
	if (gnm_debug_flag ("plugin-func"))
		g_printerr ("Activating group %s\n", sfg->category_name);
	GO_SLIST_FOREACH
		(sfg->function_name_list, char, fname,
		 GnmFunc *fd;

		 fd = gnm_func_lookup (fname, NULL);
		 if (fd) {
#if 0
			 g_printerr ("Reusing placeholder for %s\n", fname);
#endif
		 } else {
			 fd = gnm_func_add_placeholder (NULL, fname, "?");
		 }
		 if (fd->flags & GNM_FUNC_IS_PLACEHOLDER) {
			 gnm_func_set_user_data (fd, service);
			 gnm_func_upgrade_placeholder
				 (fd, sfg->func_group,
				  sfg->textdomain,
				  plugin_service_function_group_func_desc_load,
				  plugin_service_function_group_func_ref_notify);
			 if (fd->usage_count > 0)
				 g_signal_connect (go_plugin_service_get_plugin (service),
						   "state_changed",
						   G_CALLBACK (delayed_ref_notify),
						   fd);
		 } else {
			 g_warning ("Multiple definitions of function %s -- this cannot be good!", fname);
		 }
	);
	service->is_active = TRUE;
}
