test_gtk_plugin_manager_store_plugin_unloaded (TestFixture *fixture)
{
  GtkTreeIter iter;
  PeasPluginInfo *info;

  test_gtk_plugin_manager_store_plugin_loaded (fixture);

  g_assert (gtk_tree_model_get_iter_first (fixture->model, &iter));
  info = peas_gtk_plugin_manager_store_get_plugin (fixture->store, &iter);

  peas_engine_unload_plugin (fixture->engine, info);

  g_assert (!peas_gtk_plugin_manager_store_get_enabled (fixture->store, &iter));
}
