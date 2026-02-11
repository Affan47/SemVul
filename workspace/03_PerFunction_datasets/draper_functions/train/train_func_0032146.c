add_device(const char *path, DBusMessageIter *properties)
{
	struct dundee_data *info;
	int err;

	info = g_hash_table_lookup(dundee_devices, path);
	if (info != NULL)
		return;

	info = g_try_new0(struct dundee_data, 1);
	if (info == NULL)
		return;

	info->path = g_strdup(path);

	while (dbus_message_iter_get_arg_type(properties) ==
			DBUS_TYPE_DICT_ENTRY) {
		DBusMessageIter entry, value;
		const char *key;

		dbus_message_iter_recurse(properties, &entry);
		dbus_message_iter_get_basic(&entry, &key);

		dbus_message_iter_next(&entry);
		dbus_message_iter_recurse(&entry, &value);

		if (g_str_equal(key, "Active") == TRUE) {
			dbus_message_iter_get_basic(&value, &info->active);

			DBG("%s Active %d", info->path, info->active);
		} else if (g_str_equal(key, "Settings") == TRUE) {
			DBG("%s Settings", info->path);

			extract_settings(&value, info);
		} else if (g_str_equal(key, "Name") == TRUE) {
			char *name;

			dbus_message_iter_get_basic(&value, &name);

			info->name = g_strdup(name);

			DBG("%s Name %s", info->path, info->name);
		}

		dbus_message_iter_next(properties);
	}

	g_hash_table_insert(dundee_devices, g_strdup(path), info);

	err = create_device(info);
	if (err < 0)
		goto out;

	err = create_network(info);
	if (err < 0) {
		destroy_device(info);
		goto out;
	}

	if (info->active == TRUE)
		set_connected(info);

	return;

out:
	g_hash_table_remove(dundee_devices, path);
}
