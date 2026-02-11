seat_xlocal_start (Seat *seat)
{
    const gchar *xdmcp_manager = NULL;


    xdmcp_manager = seat_get_string_property (seat, "xdmcp-manager");
    if (xdmcp_manager)
    {
        SeatXLocal *s = SEAT_XLOCAL (seat);
        const gchar *key_name = NULL;
        gint port = 0;

        s->priv->xdmcp_x_server = create_x_server (seat);
        x_server_local_set_xdmcp_server (s->priv->xdmcp_x_server, xdmcp_manager);
        port = seat_get_integer_property (seat, "xdmcp-port");
        if (port > 0)
            x_server_local_set_xdmcp_port (s->priv->xdmcp_x_server, port);
        key_name = seat_get_string_property (seat, "xdmcp-key");
        if (key_name)
        {
            gchar *path;
            GKeyFile *keys;
            gboolean result;
            GError *error = NULL;

            path = g_build_filename (config_get_directory (config_get_instance ()), "keys.conf", NULL);

            keys = g_key_file_new ();
            result = g_key_file_load_from_file (keys, path, G_KEY_FILE_NONE, &error);
            if (error)
                l_debug (seat, "Error getting key %s", error->message);
            g_clear_error (&error);

            if (result)
            {
                gchar *key = NULL;

                if (g_key_file_has_key (keys, "keyring", key_name, NULL))
                    key = g_key_file_get_string (keys, "keyring", key_name, NULL);
                else
                    l_debug (seat, "Key %s not defined", key_name);

                if (key)
                    x_server_local_set_xdmcp_key (s->priv->xdmcp_x_server, key);
                g_free (key);
            }

            g_free (path);
            g_key_file_free (keys);
        }

        g_signal_connect (s->priv->xdmcp_x_server, "stopped", G_CALLBACK (xdmcp_x_server_stopped_cb), seat);
        return display_server_start (DISPLAY_SERVER (s->priv->xdmcp_x_server));
    }

    return SEAT_CLASS (seat_xlocal_parent_class)->start (seat);
}
