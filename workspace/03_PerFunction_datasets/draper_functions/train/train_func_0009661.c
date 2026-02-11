on_cursor_changed(VncConnection *conn G_GNUC_UNUSED,
                              VncCursor *cursor,
                              gpointer opaque)
{
    VncDisplay *obj = VNC_DISPLAY(opaque);
    VncDisplayPrivate *priv = obj->priv;

    VNC_DEBUG("Cursor changed %p x=%d y=%d w=%d h=%d",
              cursor,
              cursor ? vnc_cursor_get_hotx(cursor) : -1,
              cursor ? vnc_cursor_get_hoty(cursor) : -1,
              cursor ? vnc_cursor_get_width(cursor) : -1,
              cursor ? vnc_cursor_get_height(cursor) : -1);

    if (priv->remote_cursor) {
        gdk_cursor_unref(priv->remote_cursor);
        priv->remote_cursor = NULL;
    }

    if (cursor) {
        GdkDisplay *display = gtk_widget_get_display(GTK_WIDGET(obj));
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_data(vnc_cursor_get_data(cursor),
                                                     GDK_COLORSPACE_RGB,
                                                     TRUE, 8,
                                                     vnc_cursor_get_width(cursor),
                                                     vnc_cursor_get_height(cursor),
                                                     vnc_cursor_get_width(cursor) * 4,
                                                     NULL, NULL);
        priv->remote_cursor = gdk_cursor_new_from_pixbuf(display,
                                                         pixbuf,
                                                         vnc_cursor_get_hotx(cursor),
                                                         vnc_cursor_get_hoty(cursor));
        g_object_unref(pixbuf);
    }

    if (priv->in_pointer_grab) {
        do_pointer_ungrab(obj, TRUE);
        do_pointer_grab(obj, TRUE);
    } else if (priv->absolute) {
        do_pointer_hide(obj);
    }
}
