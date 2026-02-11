gdu_device_tree_model_finalize (GObject *object)
{
  GduDeviceTreeModel *model = GDU_DEVICE_TREE_MODEL (object);

  if (model->pefs_timeout_id != 0)
    g_source_remove (model->pefs_timeout_id);

  if (model->spinner_timeout != 0)
    g_source_remove (model->spinner_timeout);

  g_signal_handlers_disconnect_by_func (model->client,
                                        G_CALLBACK (on_client_changed),
                                        model);

  g_list_foreach (model->current_drives, (GFunc) g_object_unref, NULL);
  g_list_free (model->current_drives);

  g_list_foreach (model->current_mdraids, (GFunc) g_object_unref, NULL);
  g_list_free (model->current_mdraids);

  g_object_unref (model->application);

  G_OBJECT_CLASS (gdu_device_tree_model_parent_class)->finalize (object);
}
