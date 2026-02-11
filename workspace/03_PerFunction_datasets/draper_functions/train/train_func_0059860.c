_connection_closed_cb (GDBusConnection  *connection,
                       gboolean          remote_peer_vanished,
                       GError           *error,
                       IBusBus          *bus)
{
    if (error) {


        g_debug ("_connection_closed_cb: %s", error->message);
    }
    ibus_bus_close_connection (bus);
}
