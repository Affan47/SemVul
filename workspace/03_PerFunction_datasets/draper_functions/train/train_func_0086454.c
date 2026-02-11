write_message (Greeter *greeter, guint8 *message, gsize message_length)
{
    GError *error = NULL;

    g_io_channel_write_chars (greeter->priv->to_greeter_channel, (gchar *) message, message_length, NULL, &error);
    if (error)
        l_warning (greeter, "Error writing to greeter: %s", error->message);
    g_clear_error (&error);
    g_io_channel_flush (greeter->priv->to_greeter_channel, NULL);
}
