__connman_service_set_config(struct connman_service *service,
				const char *file_id, const char *entry)
{
	if (service == NULL)
		return;

	g_free(service->config_file);
	service->config_file = g_strdup(file_id);

	g_free(service->config_entry);
	service->config_entry = g_strdup(entry);
}
