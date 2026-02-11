node_has_high_bound (case_node_ptr node, tree index_type)
{
  tree high_plus_one;
  case_node_ptr pnode;


  if (TYPE_MAX_VALUE (index_type) == NULL)
    return 1;


  if (tree_int_cst_equal (node->high, TYPE_MAX_VALUE (index_type)))
    return 1;


  if (node->right)
    return 0;

  high_plus_one = fold (build (PLUS_EXPR, TREE_TYPE (node->high),
			       node->high, integer_one_node));


  if (! tree_int_cst_lt (node->high, high_plus_one))
    return 0;

  for (pnode = node->parent; pnode; pnode = pnode->parent)
    if (tree_int_cst_equal (high_plus_one, pnode->low))
      return 1;

  return 0;
}
