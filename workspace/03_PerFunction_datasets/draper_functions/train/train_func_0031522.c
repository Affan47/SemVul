_fv_text_handle_create_window (FvTextHandle         *handle,
                               FvTextHandlePosition  pos)
{
  FvTextHandlePrivate *priv;
  GdkRGBA bg = { 0, 0, 0, 0 };
  GdkWindowAttr attributes;
  GdkWindow *window;
  GdkVisual *visual;
  gint mask;

  priv = handle->priv;

  attributes.x = 0;
  attributes.y = 0;
  _fv_text_handle_get_size (handle, &attributes.width, &attributes.height);
  attributes.window_type = GDK_WINDOW_TEMP;
  attributes.wclass = GDK_INPUT_OUTPUT;
  attributes.event_mask = (GDK_EXPOSURE_MASK |
                           GDK_BUTTON_PRESS_MASK |
                           GDK_BUTTON_RELEASE_MASK |
                           GDK_BUTTON1_MOTION_MASK);

  mask = GDK_WA_X | GDK_WA_Y;

  visual = gdk_screen_get_rgba_visual (gtk_widget_get_screen (priv->parent));

  if (visual)
    {
      attributes.visual = visual;
      mask |= GDK_WA_VISUAL;
    }

  window = gdk_window_new (NULL, &attributes, mask);
  gdk_window_set_user_data (window, priv->parent);
  gdk_window_set_background_rgba (window, &bg);

  _fv_text_handle_update_shape (handle, window, pos);

  return window;
}
