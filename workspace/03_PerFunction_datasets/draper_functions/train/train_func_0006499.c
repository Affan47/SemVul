file_transfer_finish (FileTransfer  *self,
                      GAsyncResult  *result,
                      GError       **error)
{
  g_return_val_if_fail (self != NULL, FALSE);
  g_return_val_if_fail (g_simple_async_result_is_valid (result,
                                                        NULL,
                                                        file_transfer_new),
                        FALSE);

  return ! g_simple_async_result_propagate_error (G_SIMPLE_ASYNC_RESULT (result),
                                                  error);
}
