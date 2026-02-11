dump_inline_edge_summary (FILE * f, int indent, struct cgraph_node *node,
			  struct inline_summary *info)
{
  struct cgraph_edge *edge;
  for (edge = node->callees; edge; edge = edge->next_callee)
    {
      struct inline_edge_summary *es = inline_edge_summary (edge);
      struct cgraph_node *callee = cgraph_function_or_thunk_node (edge->callee, NULL);
      int i;

      fprintf (f, "%*s%s/%i %s\n%*s  loop depth:%2i freq:%4i size:%2i time: %2i callee size:%2i stack:%2i",
	       indent, "", cgraph_node_name (callee),
	       callee->uid,
	       !edge->inline_failed ? "inlined"
	       : cgraph_inline_failed_string (edge->inline_failed),
	       indent, "",
	       es->loop_depth,
               edge->frequency,
	       es->call_stmt_size,
	       es->call_stmt_time,
	       (int)inline_summary (callee)->size / INLINE_SIZE_SCALE,
	       (int)inline_summary (callee)->estimated_stack_size);

      if (es->predicate)
	{
	  fprintf (f, " predicate: ");
	  dump_predicate (f, info->conds, es->predicate);
	}
      else
	  fprintf (f, "\n");
      if (es->param)
        for (i = 0; i < (int)VEC_length (inline_param_summary_t, es->param);
	     i++)
	  {
	    int prob = VEC_index (inline_param_summary_t,
				  es->param, i)->change_prob;

	    if (!prob)
	      fprintf (f, "%*s op%i is compile time invariant\n",
		       indent + 2, "", i);
	    else if (prob != REG_BR_PROB_BASE)
	      fprintf (f, "%*s op%i change %f%% of time\n", indent + 2, "", i,
		       prob * 100.0 / REG_BR_PROB_BASE);
	  }
      if (!edge->inline_failed)
	{
          fprintf (f, "%*sStack frame offset %i, callee self size %i,"
		   " callee size %i\n",
		   indent+2, "",
		   (int)inline_summary (callee)->stack_frame_offset,
		   (int)inline_summary (callee)->estimated_self_stack_size,
		   (int)inline_summary (callee)->estimated_stack_size);
	  dump_inline_edge_summary (f, indent+2, callee, info);
	}
    }
  for (edge = node->indirect_calls; edge; edge = edge->next_callee)
    {
      struct inline_edge_summary *es = inline_edge_summary (edge);
      fprintf (f, "%*sindirect call loop depth:%2i freq:%4i size:%2i"
	       " time: %2i",
	       indent, "",
	       es->loop_depth,
               edge->frequency,
	       es->call_stmt_size,
	       es->call_stmt_time);
      if (es->predicate)
	{
	  fprintf (f, "predicate: ");
	  dump_predicate (f, info->conds, es->predicate);
	}
      else
	fprintf (f, "\n");
    }
}
