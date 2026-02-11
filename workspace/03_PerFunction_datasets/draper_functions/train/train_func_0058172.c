set_default_keyring_start (const gchar *keyring, GnomeKeyringOperationDoneCallback callback,
                           gpointer data, GDestroyNotify destroy_data)
{
	DBusMessage *req;
	const char *string;
	GkrOperation *op;
	gchar *path;

	g_return_val_if_fail (keyring, NULL);
	g_return_val_if_fail (callback, NULL);

	path = gkr_encode_keyring_name (keyring);
	req = dbus_message_new_method_call (gkr_service_name, SERVICE_PATH,
	                                    SERVICE_INTERFACE, "SetAlias");

	string = "default";
	dbus_message_append_args (req, DBUS_TYPE_STRING, &string,
	                          DBUS_TYPE_OBJECT_PATH, &path, DBUS_TYPE_INVALID);

	op = gkr_operation_new (callback, GKR_CALLBACK_RES, data, destroy_data);
	gkr_operation_set_keyring_hint (op);
	gkr_operation_request (op, req);
	dbus_message_unref (req);
	g_free (path);

	return op;
}
