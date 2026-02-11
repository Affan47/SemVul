pluginsUpdateDisplayMenu (ggobid * gg, GList * plugins)
{
  GList *el = plugins;
  OnUpdateDisplayMenu f;
  PluginInstance *plugin;
  gboolean ok = true;

  while (el) {
    plugin = (PluginInstance *) el->data;
    if (plugin->info->type == GENERAL_PLUGIN
        && plugin->info->info.g->onUpdateDisplay) {
      f =
        (OnUpdateDisplayMenu) getPluginSymbol (plugin->info->info.g->
                                               onUpdateDisplay,
                                               plugin->info->details);
      if (f) {
        ok = f (gg, plugin);
      }
    }
    el = el->next;
  }

  return (ok);
}
