gd_toggle_pixbuf_renderer_render (GtkCellRenderer      *cell,
                                  cairo_t              *cr,
                                  GtkWidget            *widget,
                                  const GdkRectangle   *background_area,
                                  const GdkRectangle   *cell_area,
                                  GtkCellRendererState  flags)
{
  gint icon_size = -1;
  GdTogglePixbufRenderer *self = GD_TOGGLE_PIXBUF_RENDERER (cell);
  gint xpad, ypad;

  GTK_CELL_RENDERER_CLASS (gd_toggle_pixbuf_renderer_parent_class)->render
    (cell, cr, widget,
     background_area, cell_area, flags);

  gtk_cell_renderer_get_padding (cell, &xpad, &ypad);
  gtk_widget_style_get (widget,
                        "check-icon-size", &icon_size,
                        NULL);

  if (icon_size == -1)
    icon_size = 40;

  render_activity (self, cr, widget, cell_area, icon_size, xpad, ypad);
  render_check (self, cr, widget, cell_area, icon_size, xpad, ypad);
}
