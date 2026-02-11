interface_get_result(const char *error,
				DBusMessageIter *iter, void *user_data)
{
	struct interface_create_data *data = user_data;
	struct supplicant_interface *interface;
	const char *path = NULL;
	int err;

	if (error != NULL)
		goto create;

	dbus_message_iter_get_basic(iter, &path);
	if (path == NULL) {
		err = -EINVAL;
		goto done;
	}

	interface = g_hash_table_lookup(interface_table, path);
	if (interface == NULL) {
		err = -ENOENT;
		goto done;
	}

	if (data->callback != NULL)
		data->callback(0, interface, data->user_data);

	dbus_free(data);

	return;

create:
	if (system_available == FALSE) {
		err = -EFAULT;
		goto done;
	}

	err = supplicant_dbus_method_call(SUPPLICANT_PATH,
						SUPPLICANT_INTERFACE,
						"CreateInterface",
						interface_create_params,
						interface_create_result, data);
	if (err == 0)
		return;

done:
	if (data->callback != NULL)
		data->callback(err, NULL, data->user_data);

	dbus_free(data);
}
