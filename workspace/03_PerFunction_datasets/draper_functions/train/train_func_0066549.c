read_from_child (GIOChannel *source, GIOCondition *condition,
                 gpointer data)
{
    CutProcessPrivate *priv = CUT_PROCESS_GET_PRIVATE(data);
    GIOStatus status;
    gsize bytes_read;
    gchar buffer[4096];

    status = g_io_channel_read_chars(source, buffer,
                                     sizeof(buffer),
                                     &bytes_read,
                                     NULL);
    g_string_append_len(priv->cutter_string, buffer, bytes_read);
    if (status == G_IO_STATUS_EOF)
        return FALSE;

    return TRUE;
}
