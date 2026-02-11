_build_async_result_and_complete        (AsyncRequestData *clos,
                                         gpointer    result,
                                         GError     *error)
{
  GSimpleAsyncResult *res = NULL;
  GObject *object = NULL;
  GCancellableData *cancellable_data = NULL;
  GCancellable *cancellable = NULL;
  gulong cancellable_id = 0;
  GAsyncReadyCallback  callback = NULL;
  gpointer source_tag;
  gpointer data;

  g_assert (clos != NULL);


  object = clos->object;
  cancellable = clos->cancellable;
  cancellable_id = clos->cancellable_id;
  callback = clos->callback;
  source_tag = clos->source_tag;
  data = clos->data;
  g_slice_free (AsyncRequestData, clos);


  cancellable_data = g_slice_new0 (GCancellableData);
  cancellable_data->cancellable = cancellable;
  cancellable_data->cancellable_id = cancellable_id;

  g_idle_add ((GSourceFunc) _disconnect_cancellable_on_idle, cancellable_data);


  res = g_simple_async_result_new (object, callback,
                                   data, source_tag);


  if (error != NULL)
    g_simple_async_result_set_from_error (res, error);
  else
    g_simple_async_result_set_op_res_gpointer (res, result, NULL);


  g_simple_async_result_complete_in_idle (res);

  g_object_unref (G_OBJECT (res));
}
