tracker_controller_dbus_start (TrackerController   *controller,
                               GError             **error)
{
	TrackerControllerPrivate *priv;
	GError *err = NULL;
	GDBusInterfaceVTable interface_vtable = {
		handle_method_call,
		NULL, NULL
	};

	priv = controller->priv;
	priv->connection = g_bus_get_sync (G_BUS_TYPE_SESSION, NULL, &err);

	if (!priv->connection) {
		g_critical ("Could not connect to the D-Bus session bus, %s",
		            err ? err->message : "no error given.");
		g_propagate_error (error, err);
		return FALSE;
	}

	priv->introspection_data = g_dbus_node_info_new_for_xml (introspection_xml, &err);
	if (!priv->introspection_data) {
		g_critical ("Could not create node info from introspection XML, %s",
		            err ? err->message : "no error given.");
		g_propagate_error (error, err);
		return FALSE;
	}

	g_message ("Registering D-Bus object...");
	g_message ("  Path:'" TRACKER_EXTRACT_PATH "'");
	g_message ("  Object Type:'%s'", G_OBJECT_TYPE_NAME (controller));

	priv->registration_id =
		g_dbus_connection_register_object (priv->connection,
		                                   TRACKER_EXTRACT_PATH,
		                                   priv->introspection_data->interfaces[0],
		                                   &interface_vtable,
		                                   controller,
		                                   NULL,
		                                   &err);

	if (err) {
		g_critical ("Could not register the D-Bus object "TRACKER_EXTRACT_PATH", %s",
		            err ? err->message : "no error given.");
		g_propagate_error (error, err);
		return FALSE;
	}

	priv->bus_name_id =
		g_bus_own_name_on_connection (priv->connection,
		                              TRACKER_EXTRACT_SERVICE,
		                              G_BUS_NAME_OWNER_FLAGS_NONE,
		                              bus_name_acquired_cb,
		                              bus_name_vanished_cb,
		                              controller, NULL);

	if (err) {
		g_critical ("Could not own the D-Bus name "TRACKER_EXTRACT_SERVICE", %s",
		            err ? err->message : "no error given.");
		g_propagate_error (error, err);
		return FALSE;
	}

	return TRUE;
}
