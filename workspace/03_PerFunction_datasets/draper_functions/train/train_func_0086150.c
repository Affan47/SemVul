seat_xvnc_create_display_server (Seat *seat, const gchar *session_type)
{
    XServerXVNC *x_server;
    const gchar *command = NULL;

    if (strcmp (session_type, "x") != 0)
        return NULL;

    x_server = x_server_xvnc_new ();
    x_server_xvnc_set_socket (x_server, g_socket_get_fd (SEAT_XVNC (seat)->priv->connection));

    command = config_get_string (config_get_instance (), "VNCServer", "command");
    if (command)
        x_server_xvnc_set_command (x_server, command);

    if (config_has_key (config_get_instance (), "VNCServer", "width") &&
        config_has_key (config_get_instance (), "VNCServer", "height"))
    {
        gint width, height;
        width = config_get_integer (config_get_instance (), "VNCServer", "width");
        height = config_get_integer (config_get_instance (), "VNCServer", "height");
        if (height > 0 && width > 0)
            x_server_xvnc_set_geometry (x_server, width, height);
    }
    if (config_has_key (config_get_instance (), "VNCServer", "depth"))
    {
        gint depth;
        depth = config_get_integer (config_get_instance (), "VNCServer", "depth");
        if (depth == 8 || depth == 16 || depth == 24 || depth == 32)
            x_server_xvnc_set_depth (x_server, depth);
    }

    return DISPLAY_SERVER (x_server);
}
