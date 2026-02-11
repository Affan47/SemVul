append_ipv6config(DBusMessageIter *iter, void *user_data)
{
	struct connman_service *service = user_data;

	if (service->ipconfig_ipv6 != NULL)
		__connman_ipconfig_append_ipv6config(service->ipconfig_ipv6,
							iter);
}
