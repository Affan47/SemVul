schedule_ebbs (void)
{
  basic_block bb;
  int probability_cutoff;
  rtx tail;

  if (profile_info && flag_branch_probabilities)
    probability_cutoff = PARAM_VALUE (TRACER_MIN_BRANCH_PROBABILITY_FEEDBACK);
  else
    probability_cutoff = PARAM_VALUE (TRACER_MIN_BRANCH_PROBABILITY);
  probability_cutoff = REG_BR_PROB_BASE / 100 * probability_cutoff;


  if (n_basic_blocks == NUM_FIXED_BLOCKS)
    return;


  {
    memcpy (&ebb_common_sched_info, &haifa_common_sched_info,
	    sizeof (ebb_common_sched_info));

    ebb_common_sched_info.fix_recovery_cfg = ebb_fix_recovery_cfg;
    ebb_common_sched_info.add_block = ebb_add_block;
    ebb_common_sched_info.sched_pass_id = SCHED_EBB_PASS;

    common_sched_info = &ebb_common_sched_info;
    sched_deps_info = &ebb_sched_deps_info;
    current_sched_info = &ebb_sched_info;
  }

  haifa_sched_init ();

  compute_bb_for_insn ();


  bitmap_initialize (&dont_calc_deps, 0);
  bitmap_clear (&dont_calc_deps);


  FOR_EACH_BB (bb)
    {
      rtx head = BB_HEAD (bb);

      for (;;)
	{
	  edge e;
	  tail = BB_END (bb);
	  if (bb->next_bb == EXIT_BLOCK_PTR
	      || LABEL_P (BB_HEAD (bb->next_bb)))
	    break;
	  e = find_fallthru_edge (bb->succs);
	  if (! e)
	    break;
	  if (e->probability <= probability_cutoff)
	    break;
	  bb = bb->next_bb;
	}


      while (head != tail)
	{
	  if (NOTE_P (head) || DEBUG_INSN_P (head))
	    head = NEXT_INSN (head);
	  else if (NOTE_P (tail) || DEBUG_INSN_P (tail))
	    tail = PREV_INSN (tail);
	  else if (LABEL_P (head))
	    head = NEXT_INSN (head);
	  else
	    break;
	}

      bb = schedule_ebb (head, tail);
    }
  bitmap_clear (&dont_calc_deps);


  if (reload_completed)
    reposition_prologue_and_epilogue_notes ();

  haifa_sched_finish ();
}
