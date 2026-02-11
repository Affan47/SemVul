regno_allocno_order_compare_func (const void *v1p, const void *v2p)
{
  ira_allocno_t a1 = *(const ira_allocno_t *) v1p;
  ira_allocno_t a2 = *(const ira_allocno_t *) v2p;
  ira_loop_tree_node_t n1 = ALLOCNO_LOOP_TREE_NODE (a1);
  ira_loop_tree_node_t n2 = ALLOCNO_LOOP_TREE_NODE (a2);

  if (loop_is_inside_p (n1, n2))
    return -1;
  else if (loop_is_inside_p (n2, n1))
    return 1;


  return ALLOCNO_NUM (a2) - ALLOCNO_NUM (a1);
}
