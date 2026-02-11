free_linked_node_tree(struct link_node *tree,
				  struct link_node **target)
{

  if (tree)
    {
      free_linked_node_tree(tree->next_sibling, target);
      free_linked_node_tree(tree->first_child, target);
      if (tree == *target)
	*target = NULL;
      if (tree->subst)
	free_context(tree->subst);
      free_link_node(tree);
    }

}
