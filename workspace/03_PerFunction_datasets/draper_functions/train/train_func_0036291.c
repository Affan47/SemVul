source_write_sync (ESource *source,
                   GCancellable *cancellable,
                   GError **error)
{
	EDBusSourceWritable *dbus_interface = NULL;
	GDBusObject *dbus_object;
	gchar *data;
	GError *local_error = NULL;

	dbus_object = e_source_ref_dbus_object (source);
	if (dbus_object != NULL) {
		dbus_interface =
			e_dbus_object_get_source_writable (
			E_DBUS_OBJECT (dbus_object));
		g_object_unref (dbus_object);
	}

	if (dbus_interface == NULL) {
		g_set_error (
			error, G_IO_ERROR,
			G_IO_ERROR_PERMISSION_DENIED,
			_("Data source '%s' is not writable"),
			e_source_get_display_name (source));
		return FALSE;
	}

	data = e_source_to_string (source, NULL);

	e_dbus_source_writable_call_write_sync (
		dbus_interface, data, cancellable, &local_error);

	g_free (data);

	g_object_unref (dbus_interface);

	if (local_error != NULL) {
		g_dbus_error_strip_remote_error (local_error);
		g_propagate_error (error, local_error);
		return FALSE;
	}

	return TRUE;
}
