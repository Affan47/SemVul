get_pixbuf_for_window (GdkDisplay *gdkdisplay,
                       guint       xid,
                       int         thumb_width,
                       int         thumb_height)
{
        GdkPixbuf *pixbuf = NULL;
#ifdef HAVE_XRENDER
        Display   *display;
        Window     xwindow;
        Pixmap     xpixmap;
        int        width;
        int        height;

        display = GDK_DISPLAY_XDISPLAY (gdkdisplay);
        xwindow = (Window) xid;

        xpixmap = get_pixmap_for_window (display, xwindow, &width, &height);

        if (xpixmap == None) {
                g_debug ("GsmInhibitDialog: Unable to get window snapshot for %u", xid);
                return NULL;
        } else {
                g_debug ("GsmInhibitDialog: Got xpixmap %u", (guint)xpixmap);
        }

        pixbuf = pixbuf_get_from_pixmap (display, xpixmap, width, height);

        if (xpixmap != None) {
                gdk_x11_display_error_trap_push (gdkdisplay);
                XFreePixmap (display, xpixmap);
                gdk_x11_display_error_trap_pop_ignored (gdkdisplay);
        }

        if (pixbuf != NULL) {
                GdkPixbuf *scaled;
                g_debug ("GsmInhibitDialog: scaling pixbuf to w=%d h=%d", width, height);
                scaled = scale_pixbuf (pixbuf, thumb_width, thumb_height, TRUE);
                g_object_unref (pixbuf);
                pixbuf = scaled;
        }
#else
        g_debug ("GsmInhibitDialog: no support for getting window snapshot");
#endif
        return pixbuf;
}
