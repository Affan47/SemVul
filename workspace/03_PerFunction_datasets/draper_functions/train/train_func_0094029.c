partition_hot_cold_basic_blocks (void)
{
  VEC(edge, heap) *crossing_edges;

  if (n_basic_blocks <= NUM_FIXED_BLOCKS + 1)
    return 0;

  df_set_flags (DF_DEFER_INSN_RESCAN);

  crossing_edges = find_rarely_executed_basic_blocks_and_crossing_edges ();
  if (crossing_edges == NULL)
    return 0;


  add_labels_and_missing_jumps (crossing_edges);


  fix_up_fall_thru_edges ();


  if (!HAS_LONG_COND_BRANCH)
    fix_crossing_conditional_branches ();


  if (!HAS_LONG_UNCOND_BRANCH)
    fix_crossing_unconditional_branches ();

  add_reg_crossing_jump_notes ();


  clear_aux_for_blocks ();

  VEC_free (edge, heap, crossing_edges);


  if (cfun->eh->lp_array)
    {
      df_finish_pass (true);
      df_scan_alloc (NULL);
      df_scan_blocks ();


      df_set_flags (DF_LR_RUN_DCE);
      df_analyze ();
    }

  return TODO_verify_flow | TODO_verify_rtl_sharing;
}
