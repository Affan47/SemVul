manager_get_devices_reply(DBusPendingCall *call, void *user_data)
{
	DBusMessage *reply;
	DBusError error;
	DBusMessageIter array, dict;
	const char *signature = DBUS_TYPE_ARRAY_AS_STRING
		DBUS_STRUCT_BEGIN_CHAR_AS_STRING
		DBUS_TYPE_OBJECT_PATH_AS_STRING
		DBUS_TYPE_ARRAY_AS_STRING
		DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
		DBUS_TYPE_STRING_AS_STRING
		DBUS_TYPE_VARIANT_AS_STRING
		DBUS_DICT_ENTRY_END_CHAR_AS_STRING
		DBUS_STRUCT_END_CHAR_AS_STRING;

	DBG("");

	reply = dbus_pending_call_steal_reply(call);

	if (dbus_message_has_signature(reply, signature) == FALSE) {
		connman_error("dundee signature does not match");
		goto done;
	}

	dbus_error_init(&error);

	if (dbus_set_error_from_message(&error, reply) == TRUE) {
		connman_error("%s", error.message);
		dbus_error_free(&error);
		goto done;
	}

	if (dbus_message_iter_init(reply, &array) == FALSE)
		goto done;

	dbus_message_iter_recurse(&array, &dict);

	while (dbus_message_iter_get_arg_type(&dict) == DBUS_TYPE_STRUCT) {
		DBusMessageIter value, properties;
		const char *path;

		dbus_message_iter_recurse(&dict, &value);
		dbus_message_iter_get_basic(&value, &path);

		dbus_message_iter_next(&value);
		dbus_message_iter_recurse(&value, &properties);

		add_device(path, &properties);

		dbus_message_iter_next(&dict);
	}

done:
	dbus_message_unref(reply);

	dbus_pending_call_unref(call);
}
