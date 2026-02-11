pluginSupportsInputMode (const gchar * modeName, GGobiPluginInfo * pluginInfo)
{
  int i;

  if (!modeName)
    return (false);

  for (i = 0; i < pluginInfo->info.i->numModeNames; i++) {
    if (strcmp (modeName, pluginInfo->info.i->modeNames[i]) == 0)
      return (true);
  }

  return (false);
}
