g_daemon_file_read_finish (GFile                  *file,
			   GAsyncResult           *res,
			   GError                **error)
{
  GSimpleAsyncResult *simple = G_SIMPLE_ASYNC_RESULT (res);
  gpointer op;

  op = g_simple_async_result_get_op_res_gpointer (simple);
  if (op)
    return g_object_ref (op);

  return NULL;
}
