enumerate_children_async_cb (GVfsDBusMount *proxy,
                             GAsyncResult *res,
                             gpointer user_data)
{
  AsyncCallEnumerate *data = user_data;
  GError *error = NULL;
  GSimpleAsyncResult *orig_result;

  orig_result = data->result;

  if (! gvfs_dbus_mount_call_enumerate_finish (proxy, res, &error))
    {
      _g_simple_async_result_take_error_stripped (orig_result, error);
      goto out;
    }

  g_object_ref (data->enumerator);

  g_simple_async_result_set_op_res_gpointer (orig_result, data->enumerator, g_object_unref);

out:
  _g_simple_async_result_complete_with_cancellable (orig_result, data->cancellable);
  _g_dbus_async_unsubscribe_cancellable (data->cancellable, data->cancelled_tag);
  data->result = NULL;
  g_object_unref (orig_result);
}
