connman_service_get_services(void)
{
	if (service_if == NULL || service_if->ordered_services == NULL)
		return NULL;

	return g_slist_copy(service_if->ordered_services);
}
