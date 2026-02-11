gc_master_init (GcMaster *master)
{
	GError *error = NULL;


	master->connection = dbus_g_bus_get (GEOCLUE_DBUS_BUS, &error);
	if (master->connection == NULL) {
		g_warning ("Could not get %s: %s", GEOCLUE_DBUS_BUS,
			   error->message);
		g_error_free (error);
	}

	master->connectivity = geoclue_connectivity_new ();

	gc_master_load_providers (master);
}
