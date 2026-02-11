add_login1_seat (GDBusConnection *connection, const gchar *id, gboolean emit_signal)
{
    Login1Seat *seat;
    GError *error = NULL;
    GDBusNodeInfo *login1_seat_info;

    const gchar *login1_seat_interface =
        "<node>"
        "  <interface name='org.freedesktop.login1.Seat'>"
        "    <property name='CanGraphical' type='b' access='read'/>"
        "    <property name='CanMultiSession' type='b' access='read'/>"
        "    <property name='Id' type='s' access='read'/>"
        "  </interface>"
        "</node>";
    static const GDBusInterfaceVTable login1_seat_vtable =
    {
        handle_login1_seat_call,
        handle_login1_seat_get_property,
    };

    seat = g_malloc0 (sizeof (Login1Seat));
    login1_seats = g_list_append (login1_seats, seat);
    seat->id = g_strdup (id);
    seat->path = g_strdup_printf ("/org/freedesktop/login1/seat/%s", seat->id);
    seat->can_graphical = TRUE;
    seat->can_multi_session = TRUE;

    login1_seat_info = g_dbus_node_info_new_for_xml (login1_seat_interface, &error);
    if (error)
        g_warning ("Failed to parse login1 seat D-Bus interface: %s", error->message);
    g_clear_error (&error);
    if (!login1_seat_info)
        return NULL;

    g_dbus_connection_register_object (connection,
                                       seat->path,
                                       login1_seat_info->interfaces[0],
                                       &login1_seat_vtable,
                                       seat,
                                       NULL,
                                       &error);
    if (error)
        g_warning ("Failed to register login1 seat: %s", error->message);
    g_clear_error (&error);
    g_dbus_node_info_unref (login1_seat_info);

    if (emit_signal)
    {
        g_dbus_connection_emit_signal (connection,
                                       NULL,
                                       "/org/freedesktop/login1",
                                       "org.freedesktop.login1.Manager",
                                       "SeatNew",
                                       g_variant_new ("(so)", seat->id, seat->path),
                                       &error);
        if (error)
            g_warning ("Failed to emit SeatNew: %s", error->message);
        g_clear_error (&error);
    }

    return seat;
}
