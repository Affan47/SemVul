has_analyzed_clone_p (struct cgraph_node *node)
{
  struct cgraph_node *orig = node;
  node = node->clones;
  if (node)
    while (node != orig)
      {
	if (node->analyzed)
	  return true;
	if (node->clones)
	  node = node->clones;
	else if (node->next_sibling_clone)
	  node = node->next_sibling_clone;
	else
	  {
	    while (node != orig && !node->next_sibling_clone)
	      node = node->clone_of;
	    if (node != orig)
	      node = node->next_sibling_clone;
	  }
      }
  return false;
}
