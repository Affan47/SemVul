grl_registry_load_plugin_list (GrlRegistry *registry,
                               GList *plugin_list)
{
  GrlPlugin *plugin;
  gboolean loaded_one = FALSE;

  while (plugin_list) {
    plugin = (GrlPlugin *) plugin_list->data;
    if (grl_plugin_get_module (plugin)) {
      loaded_one |= activate_plugin (registry, plugin, NULL);
    } else {
      loaded_one |= grl_registry_load_plugin (registry,
                                              grl_plugin_get_filename (plugin),
                                              NULL);
    }
    plugin_list = g_list_next (plugin_list);
  }

  return loaded_one;
}
