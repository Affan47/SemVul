get_icon_from_message (SoupMessage    *msg,
                       GetIconURLData *data,
                       GError        **error)
{
        GdkPixbufLoader *loader;
        GdkPixbuf       *pixbuf;

        loader = gdk_pixbuf_loader_new_with_mime_type (data->mime_type, error);
        if (loader == NULL)
                return NULL;

        gdk_pixbuf_loader_write (loader,
                                 (guchar *) msg->response_body->data,
                                 msg->response_body->length,
                                 error);
        pixbuf = gdk_pixbuf_loader_get_pixbuf (loader);
        if (pixbuf) {
                gfloat aspect_ratio;
                gint   height;


                aspect_ratio = (gfloat) data->width / data->height;
                height = (gint) (PREFERED_WIDTH / aspect_ratio);
                pixbuf = gdk_pixbuf_scale_simple (pixbuf,
                                                  PREFERED_WIDTH,
                                                  height,
                                                  GDK_INTERP_HYPER);
        }

        gdk_pixbuf_loader_close (loader, NULL);

        return pixbuf;
}
