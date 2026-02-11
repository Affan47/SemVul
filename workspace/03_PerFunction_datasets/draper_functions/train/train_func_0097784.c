get_best_auto_connection (NMDevice *dev,
                          GSList *connections,
                          char **specific_object)
{
	GSList *iter;

	for (iter = connections; iter; iter = g_slist_next (iter)) {
		NMConnection *connection = NM_CONNECTION (iter->data);

		if (!nm_connection_is_type (connection, NM_SETTING_ADSL_SETTING_NAME))
			continue;

		if (nm_connection_get_setting_adsl (connection))
			return connection;
	}
	return NULL;
}
