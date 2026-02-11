zpj_skydrive_list_folder_id_async (ZpjSkydrive *self,
                                   const gchar *folder_id,
                                   GCancellable *cancellable,
                                   GAsyncReadyCallback callback,
                                   gpointer user_data)
{
  GSimpleAsyncResult *simple;
  ZpjSkydriveThreadData *data;

  g_return_if_fail (ZPJ_IS_SKYDRIVE (self));
  g_return_if_fail (folder_id != NULL && folder_id[0] != '\0');

  simple = g_simple_async_result_new (G_OBJECT (self), callback, user_data, zpj_skydrive_list_folder_id_async);
  g_simple_async_result_set_check_cancellable (simple, cancellable);

  data = zpj_skydrive_thread_data_new (G_TYPE_POINTER, folder_id, NULL);
  g_simple_async_result_set_op_res_gpointer (simple, data, (GDestroyNotify) zpj_skydrive_thread_data_free);

  g_simple_async_result_run_in_thread (simple,
                                       zpj_skydrive_list_folder_id_in_thread_func,
                                       G_PRIORITY_DEFAULT,
                                       cancellable);
  g_object_unref (simple);
}
