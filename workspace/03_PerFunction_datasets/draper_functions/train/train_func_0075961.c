add_recent_items (ArGameChooser *chooser)
{
  ArGameChooserPrivate *priv = chooser->priv;
  const char *current_game_module;
  char **games;
  int i;

  current_game_module = aisleriot_window_get_game_module (priv->window);
  games = get_unique_recent_modules (current_game_module);

  for (i = 0; games[i] != NULL; ++i) {
    store_add_module (priv->store, games[i], MAX_RECENT - i);
  }

  g_strfreev (games);

  store_add_separator (priv->store);
}
