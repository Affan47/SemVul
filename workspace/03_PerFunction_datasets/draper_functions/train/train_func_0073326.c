vnc_connection_audio_enable(VncConnection *conn)
{
    VncConnectionPrivate *priv = conn->priv;

    if (priv->has_audio)
        {
            vnc_connection_buffered_write_u8(conn, VNC_CONNECTION_CLIENT_MESSAGE_QEMU);
            vnc_connection_buffered_write_u8(conn, VNC_CONNECTION_CLIENT_MESSAGE_QEMU_AUDIO);
            vnc_connection_buffered_write_u16(conn, VNC_CONNECTION_CLIENT_MESSAGE_QEMU_AUDIO_ENABLE);
            vnc_connection_buffered_flush(conn);
            priv->audio_enable_pending=FALSE;
        }
    else
        priv->audio_enable_pending=TRUE;
    return !vnc_connection_has_error(conn);
}
