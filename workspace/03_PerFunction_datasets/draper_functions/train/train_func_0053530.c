is_descendant(struct mailmessage_tree * node,
			 struct mailmessage_tree * maybe_child)
{
  unsigned int i;

  for(i = 0 ; i < carray_count(node->node_children) ; i++) {
    struct mailmessage_tree * tree;

    tree = carray_get(node->node_children, i);
    if (tree == maybe_child)
      return TRUE;
    if (carray_count(tree->node_children) != 0)
      if (is_descendant(tree, maybe_child))
	return TRUE;
  }

  return FALSE;
}
