photo_offscreen_window_set_max_width (PhotoOffscreenWindow *window,
                                      guint                 max_width)
{
  g_return_if_fail (PHOTO_IS_OFFSCREEN_WINDOW (window));

  if (window->priv->max_width == max_width)
    return;

  window->priv->max_width = max_width;
  g_object_notify (G_OBJECT (window), "max-width");

  gtk_widget_queue_resize (GTK_WIDGET (window));
}
