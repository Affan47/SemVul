service_property_getall (GkdSecretService *self, DBusMessage *message)
{
	DBusMessage *reply = NULL;
	DBusMessageIter iter;
	const gchar *interface;

	if (!dbus_message_get_args (message, NULL, DBUS_TYPE_STRING, &interface, DBUS_TYPE_INVALID))
		return NULL;

	if (!gkd_dbus_interface_match (SECRET_SERVICE_INTERFACE, interface))
		return dbus_message_new_error_printf (message, DBUS_ERROR_FAILED,
		                                      "Object does not have properties on interface '%s'",
		                                      interface);

	reply = dbus_message_new_method_return (message);
	dbus_message_iter_init_append (reply, &iter);
	service_append_all_properties (self, &iter);
	return reply;
}
