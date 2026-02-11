matewnck_screen_finalize (GObject *object)
{
  MatewnckScreen *screen;
  GList *tmp;
  gpointer weak_pointer;

  screen = MATEWNCK_SCREEN (object);

  unqueue_update (screen);

  for (tmp = screen->priv->stacked_windows; tmp; tmp = tmp->next)
    {
      screen->priv->mapped_windows = g_list_remove (screen->priv->mapped_windows,
                                                    tmp->data);
      _matewnck_window_destroy (MATEWNCK_WINDOW (tmp->data));
    }

  for (tmp = screen->priv->mapped_windows; tmp; tmp = tmp->next)
    _matewnck_window_destroy (MATEWNCK_WINDOW (tmp->data));

  for (tmp = screen->priv->workspaces; tmp; tmp = tmp->next)
    g_object_unref (tmp->data);

  g_list_free (screen->priv->mapped_windows);
  screen->priv->mapped_windows = NULL;
  g_list_free (screen->priv->stacked_windows);
  screen->priv->stacked_windows = NULL;

  g_list_free (screen->priv->workspaces);
  screen->priv->workspaces = NULL;

  weak_pointer = &screen->priv->active_window;
  if (screen->priv->active_window != NULL)
    g_object_remove_weak_pointer (G_OBJECT (screen->priv->active_window),
                                  weak_pointer);
  screen->priv->active_window = NULL;

  weak_pointer = &screen->priv->previously_active_window;
  if (screen->priv->previously_active_window != NULL)
    g_object_remove_weak_pointer (G_OBJECT (screen->priv->previously_active_window),
                                  weak_pointer);
  screen->priv->previously_active_window = NULL;

  g_free (screen->priv->wm_name);
  screen->priv->wm_name = NULL;

  screens[screen->priv->number] = NULL;

#ifdef HAVE_STARTUP_NOTIFICATION
  sn_display_unref (screen->priv->sn_display);
  screen->priv->sn_display = NULL;
#endif

  G_OBJECT_CLASS (matewnck_screen_parent_class)->finalize (object);
}
