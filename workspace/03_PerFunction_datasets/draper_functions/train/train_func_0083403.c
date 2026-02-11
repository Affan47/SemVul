vpn_provider_driver_unregister(struct vpn_provider_driver *driver)
{
	GHashTableIter iter;
	gpointer value, key;

	DBG("driver %p name %s", driver, driver->name);

	driver_list = g_slist_remove(driver_list, driver);

	g_hash_table_iter_init(&iter, provider_hash);
	while (g_hash_table_iter_next(&iter, &key, &value) == TRUE) {
		struct vpn_provider *provider = value;

		if (provider != NULL && provider->driver != NULL &&
				provider->driver->type == driver->type &&
				g_strcmp0(provider->driver->name,
							driver->name) == 0) {
			provider->driver = NULL;
		}
	}
}
