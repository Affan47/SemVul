peas_engine_insert_search_path (PeasEngine  *engine,
                                gint         position,
                                const gchar *module_dir,
                                const gchar *data_dir)
{
  SearchPath *sp;

  g_return_if_fail (PEAS_IS_ENGINE (engine));
  g_return_if_fail (module_dir != NULL);

  sp = g_slice_new (SearchPath);
  sp->module_dir = g_strdup (module_dir);
  sp->data_dir = g_strdup (data_dir ? data_dir : module_dir);

  engine->priv->search_paths = g_list_insert (engine->priv->search_paths,
                                              sp,
                                              position);

  g_object_freeze_notify (G_OBJECT (engine));
  load_dir_real (engine, sp->module_dir, sp->data_dir, 1);
  g_object_thaw_notify (G_OBJECT (engine));
}
