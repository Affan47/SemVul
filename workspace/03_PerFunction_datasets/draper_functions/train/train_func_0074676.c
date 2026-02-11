photos_main_window_save_geometry (PhotosMainWindow *self)
{
  PhotosMainWindowPrivate *priv = self->priv;
  GVariant *variant;
  GdkWindow *window;
  GdkWindowState state;
  gint32 position[2];
  gint32 size[2];

  window = gtk_widget_get_window (GTK_WIDGET (self));
  state = gdk_window_get_state (window);
  if (state & GDK_WINDOW_STATE_MAXIMIZED)
    return;

  gtk_window_get_size (GTK_WINDOW (self), (gint *) &size[0], (gint *) &size[1]);
  variant = g_variant_new_fixed_array (G_VARIANT_TYPE_INT32, size, 2, sizeof (size[0]));
  g_settings_set_value (priv->settings, "window-size", variant);

  gtk_window_get_position (GTK_WINDOW (self), (gint *) &position[0], (gint *) &position[1]);
  variant = g_variant_new_fixed_array (G_VARIANT_TYPE_INT32, position, 2, sizeof (position[0]));
  g_settings_set_value (priv->settings, "window-position", variant);
}
