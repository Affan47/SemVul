regmove_optimize (void)
{
  int i;
  int nregs = max_reg_num ();

  df_note_add_problem ();
  df_analyze ();

  if (flag_ira_loop_pressure)
    ira_set_pseudo_classes (dump_file);

  regstat_init_n_sets_and_refs ();
  regstat_compute_ri ();

  regno_src_regno = XNEWVEC (int, nregs);
  for (i = nregs; --i >= 0; )
    regno_src_regno[i] = -1;


  regmove_forward_pass ();


  regmove_backward_pass ();


  free (regno_src_regno);
  if (reg_set_in_bb)
    {
      free (reg_set_in_bb);
      reg_set_in_bb = NULL;
    }
  regstat_free_n_sets_and_refs ();
  regstat_free_ri ();
  if (flag_ira_loop_pressure)
    free_reg_info ();
  return 0;
}
