json_parser_load_from_stream_finish (JsonParser    *parser,
                                     GAsyncResult  *result,
                                     GError       **error)
{
  GSimpleAsyncResult *simple;
  LoadStreamData *data;

  g_return_val_if_fail (JSON_IS_PARSER (parser), FALSE);
  g_return_val_if_fail (G_IS_SIMPLE_ASYNC_RESULT (result), FALSE);

  simple = G_SIMPLE_ASYNC_RESULT (result);

  if (g_simple_async_result_propagate_error (simple, error))
    return FALSE;

  g_warn_if_fail (g_simple_async_result_get_source_tag (simple) == json_parser_load_from_stream_async);

  data = g_simple_async_result_get_op_res_gpointer (simple);

  if (data->error)
    {
      g_propagate_error (error, data->error);
      data->error = NULL;
      return FALSE;
    }

  g_byte_array_set_size (data->content, data->pos + 1);
  data->content->data[data->pos] = 0;

  return json_parser_load (parser, (const gchar *) data->content->data, data->content->len, error);
}
