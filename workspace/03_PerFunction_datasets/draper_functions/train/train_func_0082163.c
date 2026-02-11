json_gobject_deserialize (GType     gtype,
                          JsonNode *node)
{
  g_return_val_if_fail (g_type_is_a (gtype, G_TYPE_OBJECT), NULL);
  g_return_val_if_fail (JSON_NODE_TYPE (node) == JSON_NODE_OBJECT, NULL);

  return json_gobject_new (gtype, json_node_get_object (node));
}
