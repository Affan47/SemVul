json_node_init (JsonNode *node,
                JsonNodeType type)
{
  g_return_val_if_fail (type >= JSON_NODE_OBJECT &&
                        type <= JSON_NODE_NULL, NULL);

  json_node_unset (node);

  node->type = type;

  return node;
}
