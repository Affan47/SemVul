evd_http_connection_read_request_headers_finish (EvdHttpConnection  *self,
                                                 GAsyncResult       *result,
                                                 GError            **error)
{
  g_return_val_if_fail (EVD_IS_HTTP_CONNECTION (self), NULL);
  g_return_val_if_fail (g_simple_async_result_is_valid (result,
                               G_OBJECT (self),
                               evd_http_connection_read_request_headers),
                        NULL);

  if (! g_simple_async_result_propagate_error (G_SIMPLE_ASYNC_RESULT (result),
                                               error))
    {
      return g_simple_async_result_get_op_res_gpointer (G_SIMPLE_ASYNC_RESULT (result));
    }
  else
    {
      return NULL;
    }
}
