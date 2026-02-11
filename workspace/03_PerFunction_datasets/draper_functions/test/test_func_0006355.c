create_mini(GdkPixbuf * pixbuf)
{
    gint w, h;
    gfloat zoom_w, zoom_h, zoom;
    gint mini_w, mini_h;
    GdkPixbuf *res;

    w = gdk_pixbuf_get_width(pixbuf);
    h = gdk_pixbuf_get_height(pixbuf);

    zoom_w = (gfloat) w / options->thumb_width;
    zoom_h = (gfloat) h / options->thumb_height;
    zoom = MAX(zoom_w, zoom_h);

    if (zoom <= 1.0) {

        g_object_ref(pixbuf);
        return pixbuf;
    }

    mini_w = (gint) (w / zoom);
    mini_h = (gint) (h / zoom);

    mini_w = MAX(mini_w, 1);
    mini_h = MAX(mini_h, 1);

    res = gdk_pixbuf_scale_simple(pixbuf, mini_w, mini_h, GDK_INTERP_BILINEAR);

    return res;
}
