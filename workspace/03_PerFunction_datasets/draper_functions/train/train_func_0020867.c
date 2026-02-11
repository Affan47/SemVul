set_error(struct connman_service *service,
					enum connman_service_error error)
{
	const char *str;

	if (service->error == error)
		return;

	service->error = error;

	if (service->path == NULL)
		return;

	str = error2string(service->error);

	if (str == NULL)
		str = "";

	if (allow_property_changed(service) == FALSE)
		return;

	connman_dbus_property_changed_basic(service->path,
				CONNMAN_SERVICE_INTERFACE, "Error",
				DBUS_TYPE_STRING, &str);
}
