change_password_start (const char *keyring, const char *original, const char *password,
                       GnomeKeyringOperationDoneCallback callback, gpointer data,
                       GDestroyNotify destroy_data)
{
	change_password_args *args;
	DBusMessage *req;
	GkrOperation *op;
	gchar *path;

	g_return_val_if_fail (callback, NULL);

	op = gkr_operation_new (callback, GKR_CALLBACK_RES, data, destroy_data);


	if (password || original) {
		args = g_slice_new0 (change_password_args);
		args->keyring_name = g_strdup (keyring);
		args->password = egg_secure_strdup (password);
		args->original = egg_secure_strdup (original);
		gkr_operation_push (op, change_password_reply, GKR_CALLBACK_OP_SESSION,
		                    args, change_password_free);
		gkr_session_negotiate (op);

	} else {
		req = dbus_message_new_method_call (gkr_service_name, SERVICE_PATH,
		                                    SERVICE_INTERFACE, "ChangeLock");
		path = gkr_encode_keyring_name (keyring);
		dbus_message_append_args (req, DBUS_TYPE_OBJECT_PATH, &path, DBUS_TYPE_INVALID);
		gkr_operation_push (op, change_1_reply, GKR_CALLBACK_OP_MSG, path, g_free);
		gkr_operation_request (op, req);
		dbus_message_unref (req);
	}

	return op;
}
