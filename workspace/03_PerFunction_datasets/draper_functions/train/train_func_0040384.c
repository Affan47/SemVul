collection_property_get (GkdSecretObjects *self, GckObject *object, DBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *reply;
	const gchar *interface;
	const gchar *name;

	if (!dbus_message_get_args (message, NULL, DBUS_TYPE_STRING, &interface,
	                            DBUS_TYPE_STRING, &name, DBUS_TYPE_INVALID))
		return NULL;

	if (!gkd_dbus_interface_match (SECRET_COLLECTION_INTERFACE, interface))
		return dbus_message_new_error_printf (message, DBUS_ERROR_FAILED,
		                                      "Object does not have properties on interface '%s'",
		                                      interface);


	if (g_str_equal (name, "Items")) {
		reply = dbus_message_new_method_return (message);
		dbus_message_iter_init_append (reply, &iter);
		gkd_secret_objects_append_item_paths (self, dbus_message_get_path (message), &iter, message);
		return reply;
	}

	return object_property_get (object, message, name);
}
