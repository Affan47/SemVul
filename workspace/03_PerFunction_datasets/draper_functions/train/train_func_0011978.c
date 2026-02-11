garcon_menu_node_get_merge_file_filename (GarconMenuNode *node)
{
  g_return_val_if_fail (GARCON_IS_MENU_NODE (node), NULL);
  g_return_val_if_fail (node->node_type == GARCON_MENU_NODE_TYPE_MERGE_FILE, NULL);
  return node->data.merge_file.filename;
}
