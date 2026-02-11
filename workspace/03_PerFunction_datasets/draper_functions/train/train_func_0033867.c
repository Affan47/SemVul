draw(GtkWidget *widget, cairo_t *cr)
{
    GeglGtkView *self = GEGL_GTK_VIEW(widget);
    ViewHelper *priv = GET_PRIVATE(self);
    GdkRectangle rect;

    if (!priv->node)
        return FALSE;

    gdk_cairo_get_clip_rectangle(cr, &rect);

    draw_implementation(self, cr, &rect);

    return FALSE;
}
