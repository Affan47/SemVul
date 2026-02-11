test_engine_load_plugin (PeasEngine *engine)
{
  PeasPluginInfo *info;

  info = peas_engine_get_plugin_info (engine, "loadable");

  g_assert (peas_engine_load_plugin (engine, info));
  g_assert (peas_plugin_info_is_loaded (info));


  g_assert (peas_engine_load_plugin (engine, info));
}
