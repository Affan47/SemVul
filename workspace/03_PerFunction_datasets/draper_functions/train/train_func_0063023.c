DBUS_call_method(DBusConnection *connection, const char *application, const char *path, const char *interface, const char *method,
											const char *signature_in, const char *signature_out, GB_ARRAY arguments)
{
	DBusMessage *message;
	int n;
	DBusMessageIter iter;
	DBusMessage *reply;
	DBusError error;
	DBusSignatureIter siter;
	bool ret;
	GB_TYPE type;
	int nparam;

	message = dbus_message_new_method_call(application, path, interface, method);
	if (!message)
	{
		GB.Error("Couldn't allocate D-Bus message");
		return TRUE;
	}

	ret = TRUE;

	dbus_message_set_auto_start(message, TRUE);

	if (define_arguments(message, signature_in, arguments))
		goto __RETURN;


	dbus_error_init(&error);
	reply = dbus_connection_send_with_reply_and_block(connection, message, -1, &error);
	check_message(connection);

	if (dbus_error_is_set(&error))
	{
		GB.Error("&1: &2", error.name, error.message);
		if (reply)
			dbus_message_unref(reply);
		dbus_error_free(&error);
		goto __RETURN;
	}

	if (!reply)
		goto __RETURN;

	dbus_message_iter_init(reply, &iter);

	if (dbus_message_iter_get_arg_type(&iter) == DBUS_TYPE_INVALID)
	{
		GB.ReturnNull();
		ret = FALSE;
	}
	else if (!dbus_message_iter_has_next(&iter))
	{
		ret = retrieve_arg(&iter, return_value_cb, NULL);
	}
	else
	{
		GB_ARRAY result;
		GB.Array.New(POINTER(&result), GB_T_VARIANT, 0);

		do
		{
			if (retrieve_arg(&iter, add_value_cb, result))
			{
				GB.Unref(&result);
				goto __RETURN;
			}
		}
		while (dbus_message_iter_next(&iter));

		GB.ReturnObject(result);
		ret = FALSE;
	}

	dbus_message_unref(reply);

__RETURN:

	dbus_message_unref(message);

	return ret;
}
