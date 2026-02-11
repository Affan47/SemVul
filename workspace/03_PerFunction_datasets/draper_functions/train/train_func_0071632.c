interface_disconnect_result(const char *error,
				DBusMessageIter *iter, void *user_data)
{
	struct interface_disconnect_data *data = user_data;
	int result = 0;

	if (error != NULL)
		result = -EIO;

	if (data->callback != NULL)
		data->callback(result, data->user_data);

	dbus_free(data);
}
