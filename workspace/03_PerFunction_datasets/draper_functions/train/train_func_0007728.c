seat_added_cb (DisplayManager *display_manager, Seat *seat)
{
    static const GDBusInterfaceVTable seat_vtable =
    {
        handle_seat_call,
        handle_seat_get_property
    };
    gchar *path;
    BusEntry *entry;
    GError *error = NULL;

    path = g_strdup_printf ("/org/freedesktop/DisplayManager/Seat%d", seat_index);
    seat_index++;

    entry = bus_entry_new (path, NULL);
    g_free (path);
    g_hash_table_insert (seat_bus_entries, g_object_ref (seat), entry);

    g_debug ("Registering seat with bus path %s", entry->path);

    entry->bus_id = g_dbus_connection_register_object (bus,
                                                       entry->path,
                                                       seat_info->interfaces[0],
                                                       &seat_vtable,
                                                       g_object_ref (seat), g_object_unref,
                                                       &error);
    if (entry->bus_id == 0)
        g_warning ("Failed to register seat: %s", error->message);
    g_clear_error (&error);

    if (!g_dbus_connection_emit_signal (bus,
                                        NULL,
                                        "/org/freedesktop/DisplayManager",
                                        "org.freedesktop.DisplayManager",
                                        "SeatAdded",
                                        g_variant_new ("(o)", entry->path),
                                        &error))
        g_warning ("Failed to emit SeatAdded signal: %s", error->message);
    g_clear_error (&error);

    g_signal_connect (seat, "running-user-session", G_CALLBACK (running_user_session_cb), NULL);
    g_signal_connect (seat, "session-removed", G_CALLBACK (session_removed_cb), NULL);
}
