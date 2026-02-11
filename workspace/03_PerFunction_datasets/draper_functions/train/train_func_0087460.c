compute_cases_per_edge (gimple stmt)
{
  basic_block bb = gimple_bb (stmt);
  reset_out_edges_aux (bb);
  int ncases = gimple_switch_num_labels (stmt);
  for (int i = ncases - 1; i >= 1; --i)
    {
      tree elt = gimple_switch_label (stmt, i);
      tree lab = CASE_LABEL (elt);
      basic_block case_bb = label_to_block_fn (cfun, lab);
      edge case_edge = find_edge (bb, case_bb);
      case_edge->aux = (void *)((intptr_t)(case_edge->aux) + 1);
    }
}
