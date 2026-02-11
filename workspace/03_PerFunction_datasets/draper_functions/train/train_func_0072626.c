create_keyring_password_reply (GkrOperation *op, GkrSession *session, gpointer user_data)
{
	create_keyring_args *args = user_data;
	DBusMessageIter iter;
	DBusMessage *req;

	req = dbus_message_new_method_call (gkr_service_name, SERVICE_PATH,
	                                    "org.gnome.keyring.InternalUnsupportedGuiltRiddenInterface",
	                                    "CreateWithMasterPassword");

	dbus_message_iter_init_append (req, &iter);
	create_keyring_encode_properties (&iter, args->keyring_name);
	if (!gkr_session_encode_secret (session, &iter, args->password)) {
		gkr_operation_complete (op, GNOME_KEYRING_RESULT_IO_ERROR);
		dbus_message_unref (req);
		return;
	}

	gkr_operation_request (op, req);
	dbus_message_unref (req);
}
