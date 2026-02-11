service_message_handler (GkdSecretService *self, DBusMessage *message)
{
	g_return_val_if_fail (message, NULL);
	g_return_val_if_fail (GKD_SECRET_IS_SERVICE (self), NULL);


	if (dbus_message_is_method_call (message, SECRET_SERVICE_INTERFACE, "OpenSession"))
		return service_method_open_session (self, message);


	if (dbus_message_is_method_call (message, SECRET_SERVICE_INTERFACE, "CreateCollection"))
		return service_method_create_collection (self, message);


	if (dbus_message_is_method_call (message, SECRET_SERVICE_INTERFACE, "LockService"))
		return service_method_lock_service (self, message);


	if (dbus_message_is_method_call (message, SECRET_SERVICE_INTERFACE, "SearchItems"))
		return gkd_secret_objects_handle_search_items (self->objects, message, NULL, TRUE);


	if (dbus_message_is_method_call (message, SECRET_SERVICE_INTERFACE, "GetSecrets"))
		return gkd_secret_objects_handle_get_secrets (self->objects, message);


	if (dbus_message_is_method_call (message, SECRET_SERVICE_INTERFACE, "Unlock"))
		return service_method_unlock (self, message);


	if (dbus_message_is_method_call (message, SECRET_SERVICE_INTERFACE, "Lock"))
		return service_method_lock (self, message);


	if (dbus_message_is_method_call (message, INTERNAL_SERVICE_INTERFACE, "ChangeWithPrompt") ||
	    dbus_message_is_method_call (message, SECRET_SERVICE_INTERFACE, "ChangeLock"))
		return service_method_change_lock (self, message);


	if (dbus_message_is_method_call (message, SECRET_SERVICE_INTERFACE, "ReadAlias"))
		return service_method_read_alias (self, message);


	if (dbus_message_is_method_call (message, SECRET_SERVICE_INTERFACE, "SetAlias"))
		return service_method_set_alias (self, message);


	if (dbus_message_is_method_call (message, INTERNAL_SERVICE_INTERFACE, "CreateWithMasterPassword"))
		return service_method_create_with_master_password (self, message);


	if (dbus_message_is_method_call (message, INTERNAL_SERVICE_INTERFACE, "ChangeWithMasterPassword"))
		return service_method_change_with_master_password (self, message);


	if (dbus_message_is_method_call (message, INTERNAL_SERVICE_INTERFACE, "UnlockWithMasterPassword"))
		return service_method_unlock_with_master_password (self, message);


	if (dbus_message_is_method_call (message, DBUS_INTERFACE_PROPERTIES, "Get"))
		return service_property_get (self, message);


	else if (dbus_message_is_method_call (message, DBUS_INTERFACE_PROPERTIES, "Set"))
		return service_property_set (self, message);


	else if (dbus_message_is_method_call (message, DBUS_INTERFACE_PROPERTIES, "GetAll"))
		return service_property_getall (self, message);


	else if (dbus_message_has_interface (message, DBUS_INTERFACE_INTROSPECTABLE))
		return service_introspect (self, message);

	return NULL;
}
