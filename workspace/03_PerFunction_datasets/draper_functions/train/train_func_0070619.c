find_allocno_copy (ira_allocno_t a1, ira_allocno_t a2, rtx insn,
		   ira_loop_tree_node_t loop_tree_node)
{
  ira_copy_t cp, next_cp;
  ira_allocno_t another_a;

  for (cp = ALLOCNO_COPIES (a1); cp != NULL; cp = next_cp)
    {
      if (cp->first == a1)
	{
	  next_cp = cp->next_first_allocno_copy;
	  another_a = cp->second;
	}
      else if (cp->second == a1)
	{
	  next_cp = cp->next_second_allocno_copy;
	  another_a = cp->first;
	}
      else
	gcc_unreachable ();
      if (another_a == a2 && cp->insn == insn
	  && cp->loop_tree_node == loop_tree_node)
	return cp;
    }
  return NULL;
}
