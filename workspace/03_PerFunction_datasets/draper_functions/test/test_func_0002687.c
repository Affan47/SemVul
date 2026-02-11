grl_operation_set_private_data (guint                operation_id,
                                gpointer             private_data,
                                GrlOperationCancelCb cancel_cb,
                                GDestroyNotify       destroy_cb)
{
  OperationData *data = g_hash_table_lookup (operations,
                                             GUINT_TO_POINTER (operation_id));

  g_return_if_fail (data != NULL);

  data->cancel_cb    = cancel_cb;
  data->destroy_cb   = destroy_cb;
  data->private_data = private_data;
}
