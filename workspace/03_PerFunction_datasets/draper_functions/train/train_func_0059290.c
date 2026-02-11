scan_services_cb(void *user_data)
{
	if (service_if == NULL)
		return;

	if (service_if->scan_services_cb != NULL)
		service_if->scan_services_cb(service_if->refresh_user_data);
}
