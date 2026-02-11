mx_window_x11_set_position (MxNativeWindow *self, gint x, gint y)
{
  Window win;
  Display *dpy;
  ClutterStage *stage;
  MxWindowX11Private *priv;

  g_return_if_fail (MX_IS_WINDOW_X11 (self));

  priv = MX_WINDOW_X11 (self)->priv;

  stage = mx_window_get_clutter_stage (priv->window);

  if (!stage)
    return;


  if (mx_window_get_fullscreen (priv->window) ||
      mx_window_get_small_screen (priv->window))
    return;

  win = clutter_x11_get_stage_window (stage);
  dpy = clutter_x11_get_default_display ();

  XMoveWindow (dpy, win, x, y);
}
