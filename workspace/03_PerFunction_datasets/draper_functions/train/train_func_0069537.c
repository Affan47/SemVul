phonemgr_object_init (PhonemgrObject *o)
{
	DBusGConnection *conn;
	GError *e = NULL;

	if (!(conn = dbus_g_bus_get (DBUS_BUS_SESSION, &e))) {
		g_warning ("Failed to get DBUS connection: %s", e->message);
		g_error_free (e);
	} else {
		phonemgr_object_register (conn, G_OBJECT (o));

	}
}
