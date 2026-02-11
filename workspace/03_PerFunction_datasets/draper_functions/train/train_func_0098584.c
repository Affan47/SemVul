gwy_data_view_make_pixmap(GwyDataView *data_view)
{
    const GtkAllocation *alloc;
    GtkWidget *widget;
    gint width, height, scwidth, scheight;

    if (!data_view->xres || !data_view->yres) {
        gwy_object_unref(data_view->base_pixbuf);
        return;
    }

    if (data_view->base_pixbuf) {
        width = gdk_pixbuf_get_width(data_view->base_pixbuf);
        height = gdk_pixbuf_get_height(data_view->base_pixbuf);
        if (width != data_view->xres || height != data_view->yres)
            gwy_object_unref(data_view->base_pixbuf);
    }
    if (!data_view->base_pixbuf) {
        data_view->base_pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB,
                                                FALSE,
                                                BITS_PER_SAMPLE,
                                                data_view->xres,
                                                data_view->yres);
        gwy_debug_objects_creation(G_OBJECT(data_view->base_pixbuf));
    }

    if (data_view->pixbuf) {
        width = gdk_pixbuf_get_width(data_view->pixbuf);
        height = gdk_pixbuf_get_height(data_view->pixbuf);
    }
    else
        width = height = -1;

    widget = GTK_WIDGET(data_view);
    alloc = &widget->allocation;

    if (data_view->realsquare) {
        gdouble scale = MAX(data_view->xres/data_view->xreal,
                            data_view->yres/data_view->yreal);
        data_view->zoom = MIN(alloc->width/(scale*data_view->xreal),
                              alloc->height/(scale*data_view->yreal));
        scale *= data_view->zoom;
        scwidth = GWY_ROUND(scale * data_view->xreal);
        scheight = GWY_ROUND(scale * data_view->yreal);
    }
    else {
        data_view->zoom = MIN((gdouble)alloc->width/data_view->xres,
                              (gdouble)alloc->height/data_view->yres);
        scwidth = GWY_ROUND(data_view->xres * data_view->zoom);
        scheight = GWY_ROUND(data_view->yres * data_view->zoom);
    }
    data_view->xmeasure = data_view->xreal/scwidth;
    data_view->ymeasure = data_view->yreal/scheight;
    data_view->xoff = (alloc->width - scwidth)/2;
    data_view->yoff = (alloc->height - scheight)/2;
    if (scwidth != width || scheight != height) {
        gwy_object_unref(data_view->pixbuf);
        data_view->pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB,
                                           FALSE,
                                           BITS_PER_SAMPLE,
                                           scwidth, scheight);
        gwy_debug_objects_creation(G_OBJECT(data_view->pixbuf));
        gdk_pixbuf_fill(data_view->pixbuf, 0x00000000);
        gwy_data_view_paint(data_view);
    }
}
