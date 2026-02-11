test_engine_not_loadable_plugin (PeasEngine *engine)
{
  GError *error = NULL;
  PeasPluginInfo *info;

  testing_util_push_log_hook ("*libnot-loadable.so: cannot open shared "
                              "object file: No such file or directory");
  testing_util_push_log_hook ("Error loading plugin 'not-loadable'");

  info = peas_engine_get_plugin_info (engine, "not-loadable");

  g_assert (!peas_engine_load_plugin (engine, info));
  g_assert (!peas_plugin_info_is_loaded (info));
  g_assert (!peas_plugin_info_is_available (info, &error));
  g_assert_error (error, PEAS_PLUGIN_INFO_ERROR,
                  PEAS_PLUGIN_INFO_ERROR_LOADING_FAILED);

  g_error_free (error);
}
