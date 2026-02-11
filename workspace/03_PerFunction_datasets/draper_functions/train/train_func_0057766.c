panel_shell_register (gboolean replace)
{
	GBusNameOwnerFlags flags;
	guint32            request_name_reply;
	GVariant          *result;
	gboolean           retval = FALSE;
	GError            *error = NULL;

	if (dbus_connection != NULL)
		return TRUE;

	panel_cleanup_register (PANEL_CLEAN_FUNC (panel_shell_cleanup), NULL);


	dbus_connection = g_bus_get_sync (G_BUS_TYPE_SESSION, NULL, &error);
	if (dbus_connection == NULL) {
		g_warning ("Cannot register the panel shell: %s", error->message);
		goto register_out;
	}

	flags = G_BUS_NAME_OWNER_FLAGS_ALLOW_REPLACEMENT;
	if (replace)
		flags |= G_BUS_NAME_OWNER_FLAGS_REPLACE;

	result = g_dbus_connection_call_sync (dbus_connection,
					      "org.freedesktop.DBus",
					      "/org/freedesktop/DBus",
					      "org.freedesktop.DBus",
					      "RequestName",
					      g_variant_new ("(su)",
							     PANEL_DBUS_SERVICE,
							     flags),
					      G_VARIANT_TYPE ("(u)"),
					      G_DBUS_CALL_FLAGS_NONE,
					      -1, NULL, &error);
	if (!result) {
		g_warning ("Cannot register the panel shell: %s",
			   error->message);
		g_error_free (error);

		goto register_out;
	}

	g_variant_get (result, "(u)", &request_name_reply);
	g_variant_unref (result);

	switch (request_name_reply) {
	case 1:
	case 4:
		retval = TRUE;
		g_dbus_connection_signal_subscribe (dbus_connection,
						    "org.freedesktop.DBus",
						    "org.freedesktop.DBus",
						    "NameLost",
						    "/org/freedesktop/DBus",
						    PANEL_DBUS_SERVICE,
						    G_DBUS_SIGNAL_FLAGS_NONE,
						    (GDBusSignalCallback)panel_shell_on_name_lost,
						    NULL, NULL);
		break;
	case 2:
	case 3:
		g_printerr ("Cannot register the panel shell: there is "
			    "already one running.\n");
		break;
	default:
		g_warning ("Cannot register the panel shell: unhandled "
			   "reply %u from RequestName", request_name_reply);
	}

register_out:

	if (!retval) {
		panel_session_do_not_restart ();
		panel_shell_cleanup (NULL);
	}

	return retval;
}
