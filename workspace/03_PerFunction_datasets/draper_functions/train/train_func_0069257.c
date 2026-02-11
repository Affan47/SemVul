grl_registry_get_plugins (GrlRegistry *registry,
                          gboolean only_loaded)
{
  GList *plugin_list = NULL;
  GHashTableIter iter;
  GrlPlugin *current_plugin;
  gboolean is_loaded;

  g_return_val_if_fail (GRL_IS_REGISTRY (registry), NULL);

  if (only_loaded) {
    g_hash_table_iter_init (&iter, registry->priv->plugins);
    while (g_hash_table_iter_next (&iter, NULL, (gpointer *) &current_plugin)) {
      g_object_get (current_plugin, "loaded", &is_loaded, NULL);
      if (is_loaded) {
        plugin_list = g_list_prepend (plugin_list, current_plugin);
      }
    }
  } else {
    plugin_list = g_hash_table_get_keys (registry->priv->plugins);
  }

  return plugin_list;
}
