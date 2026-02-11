dump_profile_updates (struct cgraph_node *orig_node,
		      struct cgraph_node *new_node)
{
  struct cgraph_edge *cs;

  fprintf (dump_file, "    setting count of the specialized node to "
	   HOST_WIDE_INT_PRINT_DEC "\n", (HOST_WIDE_INT) new_node->count);
  for (cs = new_node->callees; cs ; cs = cs->next_callee)
    fprintf (dump_file, "      edge to %s has count "
	     HOST_WIDE_INT_PRINT_DEC "\n",
	     cgraph_node_name (cs->callee), (HOST_WIDE_INT) cs->count);

  fprintf (dump_file, "    setting count of the original node to "
	   HOST_WIDE_INT_PRINT_DEC "\n", (HOST_WIDE_INT) orig_node->count);
  for (cs = orig_node->callees; cs ; cs = cs->next_callee)
    fprintf (dump_file, "      edge to %s is left with "
	     HOST_WIDE_INT_PRINT_DEC "\n",
	     cgraph_node_name (cs->callee), (HOST_WIDE_INT) cs->count);
}
