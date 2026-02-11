create_service_entry(struct connman_service *service,
					const char *name,
					enum connman_service_state state)
{
	struct service_entry *entry;
	enum connman_service_type type;
	int idx;

	entry = g_try_new0(struct service_entry, 1);
	if (entry == NULL)
		return entry;

	entry->reason = CONNMAN_SESSION_REASON_UNKNOWN;
	entry->state = state;
	if (name != NULL)
		entry->name = name;
	else
		entry->name = "";
	entry->service = service;

	idx = __connman_service_get_index(entry->service);
	entry->ifname = connman_inet_ifname(idx);
	if (entry->ifname == NULL)
		entry->ifname = g_strdup("");

	type = connman_service_get_type(entry->service);
	entry->bearer = service2bearer(type);

	return entry;
}
