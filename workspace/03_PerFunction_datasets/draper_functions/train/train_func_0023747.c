greeter_start (Session *session)
{
    Greeter *greeter = GREETER (session);
    int to_greeter_pipe[2], from_greeter_pipe[2];
    int to_greeter_output, from_greeter_input;
    gboolean result = FALSE;
    gchar *value;


    if (pipe (to_greeter_pipe) != 0 || pipe (from_greeter_pipe) != 0)
    {
        g_warning ("Failed to create pipes: %s", strerror (errno));
        return FALSE;
    }
    to_greeter_output = to_greeter_pipe[0];
    greeter->priv->to_greeter_input = to_greeter_pipe[1];
    greeter->priv->to_greeter_channel = g_io_channel_unix_new (greeter->priv->to_greeter_input);
    g_io_channel_set_encoding (greeter->priv->to_greeter_channel, NULL, NULL);
    greeter->priv->from_greeter_output = from_greeter_pipe[0];
    from_greeter_input = from_greeter_pipe[1];
    greeter->priv->from_greeter_channel = g_io_channel_unix_new (greeter->priv->from_greeter_output);
    g_io_channel_set_encoding (greeter->priv->from_greeter_channel, NULL, NULL);
    g_io_channel_set_buffered (greeter->priv->from_greeter_channel, FALSE);
    greeter->priv->from_greeter_watch = g_io_add_watch (greeter->priv->from_greeter_channel, G_IO_IN | G_IO_HUP, read_cb, greeter);


    value = g_strdup_printf ("%d", from_greeter_input);
    session_set_env (SESSION (greeter), "LIGHTDM_TO_SERVER_FD", value);
    g_free (value);
    value = g_strdup_printf ("%d", to_greeter_output);
    session_set_env (SESSION (greeter), "LIGHTDM_FROM_SERVER_FD", value);
    g_free (value);


    fcntl (greeter->priv->to_greeter_input, F_SETFD, FD_CLOEXEC);
    fcntl (greeter->priv->from_greeter_output, F_SETFD, FD_CLOEXEC);

    result = SESSION_CLASS (greeter_parent_class)->start (session);


    close (to_greeter_output);
    close (from_greeter_input);

    return result;
}
