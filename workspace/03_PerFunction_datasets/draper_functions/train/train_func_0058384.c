gt_interval_tree_find_all_overlapping(GtIntervalTree *it,
                                           unsigned long start,
                                           unsigned long end, GtArray* a)
{
  gt_assert(it && a && start <= end);
  if (it->root == it->nil) return;
  interval_tree_find_all_internal(it, it->root, store_interval_node_in_array,
                                  start, end, a);
}
