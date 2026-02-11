json_node_set_int (JsonNode *node,
                   gint64    value)
{
  g_return_if_fail (node != NULL);
  g_return_if_fail (JSON_NODE_TYPE (node) == JSON_NODE_VALUE);

  if (node->data.value == NULL)
    node->data.value = json_value_init (json_value_alloc (), JSON_VALUE_INT);
  else
    json_value_init (node->data.value, JSON_VALUE_INT);

  json_value_set_int (node->data.value, value);
}
