brasero_caps_report_plugin_error (BraseroPlugin *plugin,
                                  BraseroForeachPluginErrorCb callback,
                                  gpointer user_data)
{
	GSList *errors;

	errors = brasero_plugin_get_errors (plugin);
	if (!errors)
		return BRASERO_BURN_ERR;

	do {
		BraseroPluginError *error;
		BraseroBurnResult result;

		error = errors->data;
		result = callback (error->type, error->detail, user_data);
		if (result == BRASERO_BURN_RETRY) {


			brasero_plugin_check_plugin_ready (plugin);
			errors = brasero_plugin_get_errors (plugin);
			continue;
		}

		if (result != BRASERO_BURN_OK)
			return result;

		errors = errors->next;
	} while (errors);

	return BRASERO_BURN_OK;
}
