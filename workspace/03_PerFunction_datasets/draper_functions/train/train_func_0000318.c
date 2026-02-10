save_update_preview(PixmapSaveControls *controls)
{
    GdkPixbuf *pixbuf;
    gdouble zoom;

    zoom = gtk_adjustment_get_value(GTK_ADJUSTMENT(controls->zoom));

    controls->args->font_size *= controls->args->zoom/zoom;
    if (controls->args->ztype == PIXMAP_NONE
        && controls->args->xytype != PIXMAP_RULERS)
        controls->args->zoom *= 1.4;

    pixbuf = pixmap_draw_presentational(controls->data, controls->args);
    gtk_image_set_from_pixbuf(GTK_IMAGE(controls->image), pixbuf);
    g_object_unref(pixbuf);

    if (controls->args->ztype == PIXMAP_NONE
        && controls->args->xytype != PIXMAP_RULERS)
        controls->args->zoom /= 1.4;
    controls->args->font_size /= controls->args->zoom/zoom;
}
