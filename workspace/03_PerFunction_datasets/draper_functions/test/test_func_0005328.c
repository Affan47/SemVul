create_transitive_part_of_edges(GtTypeNode *node,
                                            GtBoolMatrix *part_of_out_edges,
                                            GtBoolMatrix *part_of_in_edges,
                                            GtArray *node_stack)
{
  unsigned long i, j;
  if (gt_array_size(node_stack)) {
    for (i  = gt_bool_matrix_get_first_column(part_of_in_edges, node->num);
         i != gt_bool_matrix_get_last_column(part_of_in_edges, node->num);
         i  = gt_bool_matrix_get_next_column(part_of_in_edges, node->num, i)) {
      for (j = 0; j < gt_array_size(node_stack); j++) {
        GtTypeNode *child = *(GtTypeNode**) gt_array_get(node_stack, j);
        gt_bool_matrix_set(part_of_out_edges, i, child->num, true);
        gt_bool_matrix_set(part_of_in_edges, child->num, i, true);
      }
    }
  }
  gt_array_add(node_stack, node);
  for (i = 0; i < gt_array_size(node->is_a_out_edges); i++) {
    GtTypeNode *parent = *(GtTypeNode**) gt_array_get(node->is_a_out_edges, i);
    create_transitive_part_of_edges(parent, part_of_out_edges, part_of_in_edges,
                                    node_stack);
  }
  gt_array_pop(node_stack);
}
