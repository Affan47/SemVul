gdm_dbus_setup_private_server (GDBusAuthObserver  *observer,
                               GError            **error)
{
        char *guid;
        const char *client_address;
        GDBusServer *server;

        guid = g_dbus_generate_guid ();

        server = g_dbus_server_new_sync ("unix:tmpdir=/tmp",
                                         G_DBUS_SERVER_FLAGS_NONE,
                                         guid,
                                         observer,
                                         NULL,
                                         error);

        client_address = g_dbus_server_get_client_address (server);

        if (g_str_has_prefix (client_address, "unix:path=")) {
                client_address += strlen("unix:path=");
                g_chmod (client_address, 0666);
        }

        g_signal_connect (server, "new-connection",
                          G_CALLBACK (handle_connection),
                          NULL);

        g_free (guid);

        return server;
}
