item_message_handler (GkdSecretObjects *self, GckObject *object, DBusMessage *message)
{

	if (dbus_message_is_method_call (message, SECRET_ITEM_INTERFACE, "Delete"))
		return item_method_delete (self, object, message);


	else if (dbus_message_is_method_call (message, SECRET_ITEM_INTERFACE, "GetSecret"))
		return item_method_get_secret (self, object, message);


	else if (dbus_message_is_method_call (message, SECRET_ITEM_INTERFACE, "SetSecret"))
		return item_method_set_secret (self, object, message);


	if (dbus_message_is_method_call (message, DBUS_INTERFACE_PROPERTIES, "Get"))
		return item_property_get (object, message);


	else if (dbus_message_is_method_call (message, DBUS_INTERFACE_PROPERTIES, "Set"))
		return item_property_set (self, object, message);


	else if (dbus_message_is_method_call (message, DBUS_INTERFACE_PROPERTIES, "GetAll"))
		return item_property_getall (object, message);

	else if (dbus_message_has_interface (message, DBUS_INTERFACE_INTROSPECTABLE))
		return gkd_dbus_introspect_handle (message, gkd_secret_introspect_item, NULL);

	return NULL;
}
