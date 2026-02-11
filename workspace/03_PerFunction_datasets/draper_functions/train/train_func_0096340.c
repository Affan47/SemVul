cgraph_create_node (void)
{
  struct cgraph_node *node = cgraph_allocate_node ();

  node->next = cgraph_nodes;
  node->pid = -1;
  node->order = cgraph_order++;
  if (cgraph_nodes)
    cgraph_nodes->previous = node;
  node->previous = NULL;
  node->global.estimated_growth = INT_MIN;
  node->frequency = NODE_FREQUENCY_NORMAL;
  node->count_materialization_scale = REG_BR_PROB_BASE;
  ipa_empty_ref_list (&node->ref_list);
  cgraph_nodes = node;
  cgraph_n_nodes++;
  return node;
}
