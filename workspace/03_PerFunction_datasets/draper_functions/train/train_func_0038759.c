map_node_new (GrlSource *source, GList *keys)
{
  MapNode *node = g_new (MapNode, 1);
  node->source = g_object_ref (source);
  node->required_keys = g_list_copy (keys);
  node->being_queried = FALSE;

  return node;
}
