render_check (GdTogglePixbufRenderer *self,
              cairo_t                *cr,
              GtkWidget              *widget,
              const GdkRectangle     *cell_area,
              gint                    icon_size,
              gint                    xpad,
              gint                    ypad)
{
  GtkStyleContext *context;
  gint check_x, check_y, x_offset;
  GtkTextDirection direction;

  context = gtk_widget_get_style_context (widget);

  if (!self->priv->toggle_visible)
    return;

  direction = gtk_widget_get_direction (widget);
  if (direction == GTK_TEXT_DIR_RTL)
    x_offset = xpad;
  else
    x_offset = cell_area->width - icon_size - xpad;

  check_x = cell_area->x + x_offset;
  check_y = cell_area->y + cell_area->height - icon_size - ypad;

  gtk_style_context_save (context);
  gtk_style_context_add_class (context, GTK_STYLE_CLASS_CHECK);

  if (self->priv->active)
    gtk_style_context_set_state (context, GTK_STATE_FLAG_ACTIVE);

  gtk_render_check (context, cr,
                    check_x, check_y,
                    icon_size, icon_size);
  gtk_style_context_restore (context);
}
