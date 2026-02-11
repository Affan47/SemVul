gt_pch_nx_gimple_df (void *x_p)
{
  struct gimple_df * const x = (struct gimple_df *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9gimple_df))
    {
      gt_pch_n_17vec_gimple_va_gc_ ((*x).modified_noreturn_calls);
      gt_pch_n_15vec_tree_va_gc_ ((*x).ssa_names);
      gt_pch_n_9tree_node ((*x).vop);
      gt_pch_n_15bitmap_head_def ((*x).escaped.vars);
      gt_pch_n_15vec_tree_va_gc_ ((*x).free_ssanames);
      gt_pch_n_P9tree_node4htab ((*x).default_defs);
      gt_pch_n_20ssa_operand_memory_d ((*x).ssa_operands.operand_memory);
      gt_pch_n_P15tm_restart_node4htab ((*x).tm_restart);
    }
}
