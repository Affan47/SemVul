if_convert (void)
{
  basic_block bb;
  int pass;

  if (optimize == 1)
    {
      df_live_add_problem ();
      df_live_set_all_dirty ();
    }

  num_possible_if_blocks = 0;
  num_updated_if_blocks = 0;
  num_true_changes = 0;

  loop_optimizer_init (AVOID_CFG_MODIFICATIONS);
  mark_loop_exit_edges ();
  loop_optimizer_finalize ();
  free_dominance_info (CDI_DOMINATORS);


  calculate_dominance_info (CDI_POST_DOMINATORS);

  df_set_flags (DF_LR_RUN_DCE);


  pass = 0;
  do
    {
      df_analyze ();

      df_clear_flags (DF_LR_RUN_DCE);
      cond_exec_changed_p = FALSE;
      pass++;

#ifdef IFCVT_MULTIPLE_DUMPS
      if (dump_file && pass > 1)
	fprintf (dump_file, "\n\n========== Pass %d ==========\n", pass);
#endif

      FOR_EACH_BB (bb)
	{
          basic_block new_bb;
          while (!df_get_bb_dirty (bb)
                 && (new_bb = find_if_header (bb, pass)) != NULL)
            bb = new_bb;
	}

#ifdef IFCVT_MULTIPLE_DUMPS
      if (dump_file && cond_exec_changed_p)
	print_rtl_with_bb (dump_file, get_insns (), dump_flags);
#endif
    }
  while (cond_exec_changed_p);

#ifdef IFCVT_MULTIPLE_DUMPS
  if (dump_file)
    fprintf (dump_file, "\n\n========== no more changes\n");
#endif

  free_dominance_info (CDI_POST_DOMINATORS);

  if (dump_file)
    fflush (dump_file);

  clear_aux_for_blocks ();


  if (max_regno < max_reg_num ())
    max_regno = max_reg_num ();


  if (dump_file && num_possible_if_blocks > 0)
    {
      fprintf (dump_file,
	       "\n%d possible IF blocks searched.\n",
	       num_possible_if_blocks);
      fprintf (dump_file,
	       "%d IF blocks converted.\n",
	       num_updated_if_blocks);
      fprintf (dump_file,
	       "%d true changes made.\n\n\n",
	       num_true_changes);
    }

  if (optimize == 1)
    df_remove_problem (df_live);

#ifdef ENABLE_CHECKING
  verify_flow_info ();
#endif
}
