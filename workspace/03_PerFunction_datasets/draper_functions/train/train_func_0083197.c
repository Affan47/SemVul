draw_drag_dest (GladeDesignLayout *layout, cairo_t *cr, GladeWidget *drag)
{
  GladeDesignLayoutPrivate *priv = layout->priv;
  GObject *obj = glade_widget_get_object (drag);
  const double dashes = 3;
  GtkWidget *widget;
  gint x, y;

  if (!GTK_IS_WIDGET (obj))
    return;

  widget = GTK_WIDGET (obj);

  gtk_widget_translate_coordinates (widget, GTK_WIDGET (layout), 0, 0, &x, &y);
  cairo_set_line_width (cr, 2);
  cairo_set_dash (cr, &dashes, 1, 0);
  gdk_cairo_set_source_rgba (cr, &priv->frame_color_active[0]);
  cairo_rectangle (cr, x+1, y+1,
                   gtk_widget_get_allocated_width (widget)-2,
                   gtk_widget_get_allocated_height(widget)-2);
  cairo_stroke (cr);
}
