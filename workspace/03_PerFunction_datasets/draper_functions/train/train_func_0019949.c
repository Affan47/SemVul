services_changed(struct btd_device *device)
{
	DBusConnection *conn = get_dbus_connection();
	char **uuids;
	GSList *l;
	int i;

	uuids = g_new0(char *, g_slist_length(device->uuids) + 1);
	for (i = 0, l = device->uuids; l; l = l->next, i++)
		uuids[i] = l->data;

	emit_array_property_changed(conn, device->path, DEVICE_INTERFACE,
					"UUIDs", DBUS_TYPE_STRING, &uuids, i);

	g_free(uuids);
}
