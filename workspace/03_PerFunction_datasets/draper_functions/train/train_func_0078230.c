set_active_window (MatewnckScreen *screen,
                   MatewnckWindow *window)
{
  gpointer weak_pointer;

  weak_pointer = &screen->priv->active_window;


  if (screen->priv->active_window != NULL)
    g_object_remove_weak_pointer (G_OBJECT (screen->priv->active_window),
                                  weak_pointer);

  screen->priv->active_window = window;
  if (screen->priv->active_window != NULL)
    g_object_add_weak_pointer (G_OBJECT (screen->priv->active_window),
                               weak_pointer);
}
