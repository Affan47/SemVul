add_property(GDBusProxy *proxy, const char *name,
				DBusMessageIter *iter, gboolean send_changed)
{
	GDBusClient *client = proxy->client;
	DBusMessageIter value;
	struct prop_entry *prop;

	if (dbus_message_iter_get_arg_type(iter) != DBUS_TYPE_VARIANT)
		return;

	dbus_message_iter_recurse(iter, &value);

	prop = g_hash_table_lookup(proxy->prop_list, name);
	if (prop != NULL) {
		prop_entry_update(prop, &value);
		goto done;
	}

	prop = prop_entry_new(name, &value);
	if (prop == NULL)
		return;

	g_hash_table_replace(proxy->prop_list, prop->name, prop);

done:
	if (proxy->prop_func)
		proxy->prop_func(proxy, name, &value, proxy->prop_data);

	if (client == NULL || send_changed == FALSE)
		return;

	if (client->property_changed)
		client->property_changed(proxy, name, &value,
							client->user_data);
}
