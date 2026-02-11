g_daemon_file_input_stream_read_finish (GInputStream              *stream,
					GAsyncResult              *result,
					GError                   **error)
{
  GSimpleAsyncResult *simple;
  gssize nread;

  simple = G_SIMPLE_ASYNC_RESULT (result);
  g_assert (g_simple_async_result_get_source_tag (simple) == g_daemon_file_input_stream_read_async);

  nread = g_simple_async_result_get_op_res_gssize (simple);
  return nread;
}
