registerPlugin (ggobid * gg, GGobiPluginInfo * plugin)
{
  gboolean ok = true;
  OnCreate f;
  PluginInstance *inst;

  if (plugin->type != GENERAL_PLUGIN)
    return (false);

  if (!plugin->details->loaded) {
    loadPluginLibrary (plugin->details, plugin);
  }

  if (plugin->info.g->onCreate) {
    f =
      (OnCreate) getPluginSymbol (plugin->info.g->onCreate, plugin->details);
    if (f) {
      inst = (PluginInstance *) g_malloc (sizeof (PluginInstance));
      inst->data = NULL;
      inst->info = plugin;
      inst->active = true;
      ok = f (gg, plugin, inst);
      if (ok) {
        GGOBI_addPluginInstance (inst, gg);
      }
      else
        g_free (inst);
    }
    else {
      g_critical("can't locate required plugin routine %s in %s",
        plugin->info.g->onCreate, plugin->details->name);
    }
  }
  else {
    inst = (PluginInstance *) g_malloc (sizeof (PluginInstance));
    inst->data = NULL;
    inst->info = plugin;
    inst->gg = gg;
    inst->active = true;
    GGOBI_addPluginInstance (inst, gg);
  }
  return (ok);
}
