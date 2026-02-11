simple_edge_hints (struct cgraph_edge *edge)
{
  int hints = 0;
  struct cgraph_node *to = (edge->caller->global.inlined_to
			    ? edge->caller->global.inlined_to : edge->caller);
  if (inline_summary (to)->scc_no
      && inline_summary (to)->scc_no == inline_summary (edge->callee)->scc_no
      && !cgraph_edge_recursive_p (edge))
    hints |= INLINE_HINT_same_scc;

  if (to->symbol.lto_file_data && edge->callee->symbol.lto_file_data
      && to->symbol.lto_file_data != edge->callee->symbol.lto_file_data)
    hints |= INLINE_HINT_cross_module;

  return hints;
}
