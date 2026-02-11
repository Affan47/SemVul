evd_http_connection_unread_request_headers (EvdHttpConnection   *self,
                                            EvdHttpRequest      *request,
                                            GError             **error)
{
  GInputStream *stream;
  gboolean result = TRUE;
  gchar *buf;
  gsize size;

  g_return_val_if_fail (EVD_IS_HTTP_CONNECTION (self), FALSE);
  g_return_val_if_fail (EVD_IS_HTTP_REQUEST (request), FALSE);

  buf = evd_http_request_to_string (request, &size);

  stream = g_io_stream_get_input_stream (G_IO_STREAM (self));
  if (evd_buffered_input_stream_unread (EVD_BUFFERED_INPUT_STREAM (stream),
                                        buf,
                                        size,
                                        NULL,
                                        error) < 0)
    result = FALSE;

  g_free (buf);

  return result;
}
