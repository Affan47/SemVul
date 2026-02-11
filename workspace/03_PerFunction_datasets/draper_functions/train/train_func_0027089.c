__connman_config_provision_service_ident(struct connman_service *service,
			const char *ident, const char *file, const char *entry)
{
	enum connman_service_type type;
	struct connman_config *config;
	int ret = 0;


	type = connman_service_get_type(service);

	DBG("service %p type %d", service, type);

	if (type != CONNMAN_SERVICE_TYPE_WIFI &&
					type != CONNMAN_SERVICE_TYPE_ETHERNET)
		return -ENOSYS;

	config = g_hash_table_lookup(config_table, ident);
	if (config != NULL) {
		GHashTableIter iter;
		gpointer value, key;
		gboolean found = FALSE;

		g_hash_table_iter_init(&iter, config->service_table);


		if (file != NULL && entry != NULL) {
			while (g_hash_table_iter_next(&iter, &key,
							&value) == TRUE) {
				struct connman_config_service *config_service;

				config_service = value;

				if (g_strcmp0(config_service->config_ident,
								file) != 0)
					continue;

				if (g_strcmp0(config_service->config_entry,
								entry) != 0)
					continue;

				found = TRUE;
				break;
			}

			DBG("found %d ident %s file %s entry %s", found, ident,
								file, entry);

			if (found == FALSE) {


				g_hash_table_remove(config->service_table,
						entry + 8);
				ret = 1;
			}
		}

		g_hash_table_foreach(config->service_table,
						provision_service, service);
	}

	return ret;
}
