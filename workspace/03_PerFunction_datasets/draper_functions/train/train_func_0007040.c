test_extension_garbage_collect (PeasEngine     *engine,
                                PeasPluginInfo *info)
{
  peas_engine_garbage_collect (engine);


  g_assert (peas_engine_unload_plugin (engine, info));
  peas_engine_garbage_collect (engine);
}
