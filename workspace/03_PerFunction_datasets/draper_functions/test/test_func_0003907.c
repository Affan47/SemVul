json_reader_is_value (JsonReader *reader)
{
  g_return_val_if_fail (JSON_IS_READER (reader), FALSE);
  json_reader_return_val_if_error_set (reader, FALSE);

  if (reader->priv->current_node == NULL)
    return FALSE;

  return JSON_NODE_HOLDS_VALUE (reader->priv->current_node) ||
         JSON_NODE_HOLDS_NULL (reader->priv->current_node);
}
