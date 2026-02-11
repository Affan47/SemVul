destroy_property(gpointer user_data)
{
	struct property_change *property = user_data;
	struct connman_service *service;

	if (property == NULL)
		return;

	service = get_service(property->path);
	if (service != NULL) {
		if (property->error != 0)
			service->to_error[property->index] = 0;
		else
			service->to_update[property->index] = 0;
	}

	g_free(property);
}
