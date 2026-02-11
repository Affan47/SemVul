set_allocno_reg (ira_allocno_t allocno, rtx reg)
{
  int regno;
  ira_allocno_t a;
  ira_loop_tree_node_t node;

  node = ALLOCNO_LOOP_TREE_NODE (allocno);
  for (a = ira_regno_allocno_map[ALLOCNO_REGNO (allocno)];
       a != NULL;
       a = ALLOCNO_NEXT_REGNO_ALLOCNO (a))
    if (subloop_tree_node_p (ALLOCNO_LOOP_TREE_NODE (a), node))
      ALLOCNO_REG (a) = reg;
  for (a = ALLOCNO_CAP (allocno); a != NULL; a = ALLOCNO_CAP (a))
    ALLOCNO_REG (a) = reg;
  regno = ALLOCNO_REGNO (allocno);
  for (a = allocno;;)
    {
      if (a == NULL || (a = ALLOCNO_CAP (a)) == NULL)
	{
	  node = node->parent;
	  if (node == NULL)
	    break;
	  a = node->regno_allocno_map[regno];
	}
      if (a == NULL)
	continue;
      if (ALLOCNO_CHILD_RENAMED_P (a))
	break;
      ALLOCNO_CHILD_RENAMED_P (a) = true;
    }
}
