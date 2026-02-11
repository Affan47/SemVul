wnck_window_is_active (WnckWindow *window)
{
  g_return_val_if_fail (WNCK_IS_WINDOW (window), FALSE);

  return window == wnck_screen_get_active_window (window->priv->screen);
}
