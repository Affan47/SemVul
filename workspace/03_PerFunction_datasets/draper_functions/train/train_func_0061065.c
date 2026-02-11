probe_driver(struct connman_network_driver *driver)
{
	GSList *list;

	DBG("driver %p name %s", driver, driver->name);

	for (list = network_list; list != NULL; list = list->next) {
		struct connman_network *network = list->data;

		if (network->driver != NULL)
			continue;

		if (driver->type != network->type)
			continue;

		if (driver->probe(network) < 0)
			continue;

		network->driver = driver;
	}
}
