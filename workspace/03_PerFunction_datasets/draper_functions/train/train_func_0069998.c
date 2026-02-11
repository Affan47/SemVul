go_plugin_db_deactivate_plugin_list (GSList *plugins, GOErrorInfo **ret_error)
{
	GSList *error_list = NULL;

	GO_INIT_RET_ERROR_INFO (ret_error);
	GO_SLIST_FOREACH (plugins, GOPlugin, plugin,
		GOErrorInfo *error;

		go_plugin_deactivate (plugin, &error);
		if (error != NULL) {
			GOErrorInfo *new_error;

			new_error = go_error_info_new_printf (
			            _("Couldn't deactivate plugin \"%s\" (ID: %s)."),
			            plugin->name, plugin->id);
			go_error_info_add_details (new_error, error);
			GO_SLIST_PREPEND (error_list, new_error);
		}
	);
	if (error_list != NULL) {
		GO_SLIST_REVERSE (error_list);
		*ret_error = go_error_info_new_from_error_list (error_list);
	}
}
