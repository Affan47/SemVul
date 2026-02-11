backward(struct link_node **tree,
				  struct link_node *node,
				  struct link_node **target,
				  int *nopen,
				  int *nres)
{

  struct link_node *p, *start, *temp_p;
  BOOLEAN left_most, target_here;

  if (node->first_child)
    {
      printf("attempted to back up from a node with a child\n");
      exit(ABEND_EXIT);
    }

  clear_subst_1(node->tr);

  node->first = TRUE;
  node->current_clause = NULL;


  node->unit_deleted = FALSE;
  if (node->goal_to_resolve)
    {
      zap_term(node->goal_to_resolve);


      node->goal_to_resolve = NULL;
    }

  if (node->prev_sibling)
    {
      if (node->prev_sibling == *target)
	{
	  if ((*target)->prev_sibling)
	    {
	      left_most = FALSE;
	      start = node;
	    }
	  else
	    {
	      left_most = TRUE;
	      start = *target;
	    }
	}
      else
	{
	  left_most = FALSE;
	  start = node;
	}
    }
  else
    {
      left_most = TRUE;
      start = node;
    }

  if (!left_most)
    {

      node->farthest_sat = (node->parent)->farthest_sat + 1;
      p = start->prev_sibling;
      if (p == *target)
	p = p->prev_sibling;
      while (p->first_child)
	{
	  p = p->first_child;

	  while (p->next_sibling)
	    p = p->next_sibling;
	}
      if (p == *target)

	p = backward(tree, p, target, nopen, nres);
      else
	{
	  *nopen = *nopen + 1;
	  *nres = *nres - 1;
	  p->current_clause = NULL;
	}
    }
  else
    {


      if (keep_clause(start, target, &target_here, nopen))
	p = start;
      else
	{


	  p = start->parent;

	  if (target_here)
	    *nopen = *nopen - (num_literals(p->current_clause) - 2);
	  else
	    *nopen = *nopen - (num_literals(p->current_clause) - 1);
	  while (p->first_child)
	    {
	      temp_p = p->first_child;
	      p->first_child = temp_p->next_sibling;
	      free_context(temp_p->subst);
	      free_link_node(temp_p);
	    }
	  if (p == *tree)
	    {

	      free_context(p->subst);
	      free_link_node(p);
	      p = NULL;
	      *tree = NULL;
	      *nopen = *nopen - 1;
	    }
	  else
	    {

	      *nres = *nres - 1;
	      *nopen = *nopen + 1;
	      p->current_clause = NULL;
	    }
	}
    }

  return p;

}
