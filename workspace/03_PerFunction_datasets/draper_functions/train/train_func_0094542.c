remove_all_occurrences (forest_node)
     et_forest_node_t forest_node;
{
  et_forest_occurrence_t first = forest_node->first;
  et_forest_occurrence_t last = forest_node->last;
  et_forest_occurrence_t node;

  splay (first);

  if (first->left)
    first->left->parent = 0;
  if (first->right)
    first->right->parent = 0;

  if (last != first)
    {
      splay (last);

      if (last->left)
	last->left->parent = 0;
      if (last->right)
	last->right->parent = 0;
    }

  if (last->right && first->left)
    {

      et_forest_occurrence_t prev_node, next_node;

      prev_node = splay (find_rightmost_node (first->left));
      next_node = splay (find_leftmost_node (last->right));


      if (prev_node->next != next_node)
	abort ();

      prev_node->right = next_node->right;
      prev_node->count_right = next_node->count_right;
      prev_node->next = next_node->next;
      if (prev_node->right)
	prev_node->right->parent = prev_node;

      if (prev_node->node->last == next_node)
	prev_node->node->last = prev_node;

      free (next_node);
    }

  if (first != last)
    {
      node = first->next;

      while (node != last)
	{
	  et_forest_occurrence_t next_node;

	  splay (node);

	  if (node->left)
	    node->left->parent = 0;
	  if (node->right)
	    node->right->parent = 0;

	  next_node = node->next;
	  free (node);
	  node = next_node;
	}
    }

  free (first);
  if (first != last)
    free (last);
}
