on_bus_acquired (GDBusConnection    *connection,
		  const gchar        *name,
		  PanelAppletFactory *factory)
{
	gchar  *object_path;
	GError *error = NULL;

	if (!introspection_data)
		introspection_data = g_dbus_node_info_new_for_xml (introspection_xml, NULL);
	object_path = g_strdup_printf (PANEL_APPLET_FACTORY_OBJECT_PATH, factory->factory_id);
	g_dbus_connection_register_object (connection,
					   object_path,
					   introspection_data->interfaces[0],
					   &interface_vtable,
					   factory, NULL,
					   &error);
	if (error) {
		g_printerr ("Failed to register object %s: %s\n", object_path, error->message);
		g_error_free (error);
	}

	g_free (object_path);
}
