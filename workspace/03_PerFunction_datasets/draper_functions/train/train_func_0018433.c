test_copy_object (void)
{
  JsonObject *obj = json_object_new ();
  JsonNode *node = json_node_new (JSON_NODE_OBJECT);
  JsonNode *value = json_node_new (JSON_NODE_VALUE);
  JsonNode *copy;

  json_node_set_int (value, 42);
  json_object_set_member (obj, "answer", value);

  json_node_take_object (node, obj);

  copy = json_node_copy (node);

  g_assert_cmpint (json_node_get_node_type (node), ==, json_node_get_node_type (copy));
  g_assert (json_node_get_object (node) == json_node_get_object (copy));

  json_node_free (copy);
  json_node_free (node);
}
