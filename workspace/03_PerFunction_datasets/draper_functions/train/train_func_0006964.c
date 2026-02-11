prv_read_keys(dleyna_settings_t *settings)
{
	GError *error = NULL;
	GKeyFile *keyfile = settings->keyfile;
	gboolean b_val;
	gint int_val;
	gchar *s_val;
	gint *int_star;
	gsize length;
	gchar **list;

	b_val = g_key_file_get_boolean(keyfile,
				       DLEYNA_SETTINGS_GROUP_GENERAL,
				       DLEYNA_SETTINGS_KEY_NEVER_QUIT,
				       &error);

	if (error == NULL) {
		settings->never_quit = b_val;
	} else {
		g_error_free(error);
		error = NULL;
	}

	s_val = g_key_file_get_string(keyfile,
				      DLEYNA_SETTINGS_GROUP_GENERAL,
				      DLEYNA_SETTINGS_KEY_CONNECTOR_NAME,
				       &error);

	if (error == NULL) {
		g_free(settings->connector_name);
		settings->connector_name = s_val;
	} else {
		g_error_free(error);
		error = NULL;
	}

	int_val = g_key_file_get_integer(keyfile,
					 DLEYNA_SETTINGS_GROUP_LOG,
					 DLEYNA_SETTINGS_KEY_LOG_TYPE,
					 &error);

	if (error == NULL) {
		settings->log_type = prv_to_log_type(int_val);
	} else {
		g_error_free(error);
		error = NULL;
	}

	g_key_file_set_list_separator(keyfile, ',');

	int_star = g_key_file_get_integer_list(keyfile,
					       DLEYNA_SETTINGS_GROUP_LOG,
					       DLEYNA_SETTINGS_KEY_LOG_LEVEL,
					       &length,
					       &error);

	if (error == NULL) {
		settings->log_level = prv_to_log_level(int_star, length);
		g_free(int_star);
	} else {
		g_error_free(error);
		error = NULL;
	}

	b_val = g_key_file_get_boolean(keyfile,
				       DLEYNA_SETTINGS_GROUP_NETF,
				       DLEYNA_SETTINGS_KEY_NETF_ENABLED,
				       &error);

	if (error == NULL) {
		settings->netf_enabled = b_val;
	} else {
		g_error_free(error);
		error = NULL;
	}

	list = g_key_file_get_string_list(keyfile,
					  DLEYNA_SETTINGS_GROUP_NETF,
					  DLEYNA_SETTINGS_KEY_NETF_LIST,
					  NULL,
					  &error);

	if (error == NULL) {
		settings->netf_entries = prv_to_netf_entries(list);
		g_strfreev(list);
	} else {
		g_error_free(error);
		error = NULL;
	}
}
