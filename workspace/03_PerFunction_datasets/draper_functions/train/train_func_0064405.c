json_array_get_null_element (JsonArray *array,
                             guint      index_)
{
  JsonNode *node;

  g_return_val_if_fail (array != NULL, FALSE);
  g_return_val_if_fail (index_ < array->elements->len, FALSE);

  node = g_ptr_array_index (array->elements, index_);
  g_return_val_if_fail (node != NULL, FALSE);

  if (JSON_NODE_HOLDS_NULL (node))
    return TRUE;

  if (JSON_NODE_HOLDS_ARRAY (node))
    return json_node_get_array (node) == NULL;

  if (JSON_NODE_HOLDS_OBJECT (node))
    return json_node_get_object (node) == NULL;

  return FALSE;
}
