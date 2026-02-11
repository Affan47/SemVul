g_dbus_emit_property_changed(DBusConnection *connection,
				const char *path, const char *interface,
				const char *name)
{
	const GDBusPropertyTable *property;
	struct generic_data *data;
	struct interface_data *iface;

	if (path == NULL)
		return;

	if (!dbus_connection_get_object_path_data(connection, path,
					(void **) &data) || data == NULL)
		return;

	iface = find_interface(data->interfaces, interface);
	if (iface == NULL)
		return;


	if (root && g_slist_find(data->added, iface))
		return;

	property = find_property(iface->properties, name);
	if (property == NULL) {
		error("Could not find property %s in %p", name,
							iface->properties);
		return;
	}

	if (g_slist_find(iface->pending_prop, (void *) property) != NULL)
		return;

	data->pending_prop = TRUE;
	iface->pending_prop = g_slist_prepend(iface->pending_prop,
						(void *) property);

	if (!data->process_id) {
		data->process_id = g_idle_add(process_changes, data);
		return;
	}
}
