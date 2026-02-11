loop_compare_func (const void *v1p, const void *v2p)
{
  int diff;
  ira_loop_tree_node_t l1 = *(const ira_loop_tree_node_t *) v1p;
  ira_loop_tree_node_t l2 = *(const ira_loop_tree_node_t *) v2p;

  ira_assert (l1->parent != NULL && l2->parent != NULL);
  if (l1->to_remove_p && ! l2->to_remove_p)
    return -1;
  if (! l1->to_remove_p && l2->to_remove_p)
    return 1;
  if ((diff = l1->loop->header->frequency - l2->loop->header->frequency) != 0)
    return diff;
  if ((diff = (int) loop_depth (l1->loop) - (int) loop_depth (l2->loop)) != 0)
    return diff;

  return l1->loop_num - l2->loop_num;
}
