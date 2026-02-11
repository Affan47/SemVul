gt_pch_nx_cgraph_edge (void *x_p)
{
  struct cgraph_edge * x = (struct cgraph_edge *)x_p;
  struct cgraph_edge * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_11cgraph_edge))
   xlimit = ((*xlimit).next_caller);
  if (x != xlimit)
    for (;;)
      {
        struct cgraph_edge * const xprev = ((*x).prev_caller);
        if (xprev == NULL) break;
        x = xprev;
        (void) gt_pch_note_object (xprev, xprev, gt_pch_p_11cgraph_edge);
      }
  while (x != xlimit)
    {
      gt_pch_n_11cgraph_node ((*x).caller);
      gt_pch_n_11cgraph_node ((*x).callee);
      gt_pch_n_11cgraph_edge ((*x).prev_caller);
      gt_pch_n_11cgraph_edge ((*x).next_caller);
      gt_pch_n_11cgraph_edge ((*x).prev_callee);
      gt_pch_n_11cgraph_edge ((*x).next_callee);
      gt_pch_n_18gimple_statement_d ((*x).call_stmt);
      gt_pch_n_25cgraph_indirect_call_info ((*x).indirect_info);
      x = ((*x).next_caller);
    }
}
