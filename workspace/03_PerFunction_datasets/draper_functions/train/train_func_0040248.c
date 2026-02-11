setup_async_wrapper (GMount *mount,
                     GAsyncReadyCallback  callback,
                     gpointer             user_data)
{
  AsyncWrapperOp *data;

  data = g_new0 (AsyncWrapperOp, 1);
  data->object = g_object_ref (mount);
  data->callback = callback;
  data->user_data = user_data;
  return data;
}
