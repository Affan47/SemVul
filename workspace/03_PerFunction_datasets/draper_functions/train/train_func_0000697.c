handle_connected (LightDMGreeter *greeter, guint8 *message, gsize message_length, gsize *offset)
{
    LightDMGreeterPrivate *priv = GET_PRIVATE (greeter);
    gchar *version;
    GString *hint_string;
    int timeout;

    version = read_string (message, message_length, offset);
    hint_string = g_string_new ("");
    while (*offset < message_length)
    {
        gchar *name, *value;

        name = read_string (message, message_length, offset);
        value = read_string (message, message_length, offset);
        g_hash_table_insert (priv->hints, name, value);
        g_string_append_printf (hint_string, " %s=%s", name, value);
    }

    g_debug ("Connected version=%s%s", version, hint_string->str);
    g_free (version);
    g_string_free (hint_string, TRUE);


    timeout = lightdm_greeter_get_autologin_timeout_hint (greeter);
    if (timeout)
    {
        g_debug ("Setting autologin timer for %d seconds", timeout);
        priv->autologin_timeout = g_timeout_add (timeout * 1000, timed_login_cb, greeter);
    }
}
