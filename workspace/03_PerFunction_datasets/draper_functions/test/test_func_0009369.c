vnc_connection_raw_update(VncConnection *conn,
                                      guint16 x, guint16 y,
                                      guint16 width, guint16 height)
{
    VncConnectionPrivate *priv = conn->priv;


    if (vnc_framebuffer_perfect_format_match(priv->fb)) {
        int i;
        int rowstride = vnc_framebuffer_get_rowstride(priv->fb);
        guint8 *dst = vnc_framebuffer_get_buffer(priv->fb);

        dst += (y * rowstride) + (x * (priv->fmt.bits_per_pixel/8));

        for (i = 0; i < height; i++) {
            vnc_connection_read(conn, dst,
                                width * (priv->fmt.bits_per_pixel/8));
            dst += rowstride;
        }
    } else {
        guint8 *dst;
        int i;

        dst = g_malloc(width * (priv->fmt.bits_per_pixel / 8));
        for (i = 0; i < height; i++) {
            vnc_connection_read(conn, dst, width * (priv->fmt.bits_per_pixel / 8));
            vnc_framebuffer_blt(priv->fb, dst, 0, x, y + i, width, 1);
        }
        g_free(dst);
    }
}
