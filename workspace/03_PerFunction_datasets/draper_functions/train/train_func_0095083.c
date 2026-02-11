ipa_get_nodes_in_cycle (struct cgraph_node *node)
{
  vec<cgraph_node_ptr> v = vNULL;
  struct ipa_dfs_info *node_dfs_info;
  while (node)
    {
      v.safe_push (node);
      node_dfs_info = (struct ipa_dfs_info *) node->symbol.aux;
      node = node_dfs_info->next_cycle;
    }
  return v;
}
