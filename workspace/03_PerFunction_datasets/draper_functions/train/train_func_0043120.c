connman_resolver_append_lifetime(int index, const char *domain,
				const char *server, unsigned int lifetime)
{
	GSList *list;
	unsigned int interval;

	DBG("index %d domain %s server %s lifetime %d",
				index, domain, server, lifetime);

	if (server == NULL && domain == NULL)
		return -EINVAL;

	for (list = entry_list; list; list = list->next) {
		struct entry_data *entry = list->data;

		if (entry->timeout == 0 ||
				entry->index != index ||
				g_strcmp0(entry->domain, domain) != 0 ||
				g_strcmp0(entry->server, server) != 0)
			continue;

		g_source_remove(entry->timeout);

		if (lifetime == 0) {
			resolver_expire_cb(entry);
			return 0;
		}

		interval = lifetime * RESOLVER_LIFETIME_REFRESH_THRESHOLD;

		DBG("RDNSS start index %d domain %s "
				"server %s lifetime threshold %d",
				index, domain, server, interval);

		entry->timeout = g_timeout_add_seconds(interval,
				resolver_refresh_cb, entry);
		return 0;
	}

	return append_resolver(index, domain, server, lifetime, 0);
}
