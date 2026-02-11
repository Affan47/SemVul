gt_type_node_part_of_get(const GtTypeNode *type_node,
                                  unsigned long idx)
{
  gt_assert(type_node && idx < gt_type_node_part_of_size(type_node));
  return *(const char**) gt_array_get(type_node->part_of_list, idx);
}
