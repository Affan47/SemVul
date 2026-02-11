vnc_connection_pixel_format(VncConnection *conn)
{
    VncConnectionPrivate *priv = conn->priv;
    struct signal_data sigdata;

    if (priv->has_error)
        return;

    sigdata.params.pixelFormat = &priv->fmt;
    vnc_connection_emit_main_context(conn, VNC_PIXEL_FORMAT_CHANGED, &sigdata);
}
