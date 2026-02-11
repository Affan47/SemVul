session_removed_cb (Seat *seat, Session *session)
{
    BusEntry *entry;

    g_signal_handlers_disconnect_matched (session, G_SIGNAL_MATCH_DATA, 0, 0, NULL, NULL, seat);

    entry = g_hash_table_lookup (session_bus_entries, session);
    if (entry)
    {
        GError *error = NULL;

        g_dbus_connection_unregister_object (bus, entry->bus_id);
        if (!g_dbus_connection_emit_signal (bus,
                                            NULL,
                                            "/org/freedesktop/DisplayManager",
                                            "org.freedesktop.DisplayManager",
                                            "SessionRemoved",
                                            g_variant_new ("(o)", entry->path),
                                            &error))
            g_warning ("Failed to emit SessionRemoved signal: %s", error->message);
        g_clear_error (&error);
    }

    g_hash_table_remove (session_bus_entries, session);
}
