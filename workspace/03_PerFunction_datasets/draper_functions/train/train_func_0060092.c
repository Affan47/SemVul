get_best_auto_connection (NMDevice *dev,
                          GSList *connections,
                          char **specific_object)
{
	GSList *iter;

	for (iter = connections; iter; iter = g_slist_next (iter)) {
		NMConnection *connection = NM_CONNECTION (iter->data);

		if (match_vlan_connection (NM_DEVICE_VLAN (dev), connection, NULL))
			return connection;
	}
	return NULL;
}
