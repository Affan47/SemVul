photo_offscreen_window_get_preferred_height (GtkWidget *widget,
                                             gint      *minimum,
                                             gint      *natural)
{
  PhotoOffscreenWindow *window = PHOTO_OFFSCREEN_WINDOW (widget);

  GTK_WIDGET_CLASS (photo_offscreen_window_parent_class)->get_preferred_height (widget, minimum, natural);

  if (window->priv->max_height > 0) {
    *minimum = MIN (*minimum, window->priv->max_height);
    *natural = MIN (*natural, window->priv->max_height);
  }
}
