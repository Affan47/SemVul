peephole2_optimize (void)
{
  rtx insn;
  bitmap live;
  int i;
  basic_block bb;

  peep2_do_cleanup_cfg = false;
  peep2_do_rebuild_jump_labels = false;

  df_set_flags (DF_LR_RUN_DCE);
  df_note_add_problem ();
  df_analyze ();


  for (i = 0; i < MAX_INSNS_PER_PEEP2 + 1; ++i)
    peep2_insn_data[i].live_before = BITMAP_ALLOC (&reg_obstack);
  search_ofs = 0;
  live = BITMAP_ALLOC (&reg_obstack);

  FOR_EACH_BB_REVERSE (bb)
    {
      bool past_end = false;
      int pos;

      rtl_profile_for_bb (bb);


      bitmap_copy (live, DF_LR_IN (bb));
      df_simulate_initialize_forwards (bb, live);
      peep2_reinit_state (live);

      insn = BB_HEAD (bb);
      for (;;)
	{
	  rtx attempt, head;
	  int match_len;

	  if (!past_end && !NONDEBUG_INSN_P (insn))
	    {
	    next_insn:
	      insn = NEXT_INSN (insn);
	      if (insn == NEXT_INSN (BB_END (bb)))
		past_end = true;
	      continue;
	    }
	  if (!past_end && peep2_fill_buffer (bb, insn, live))
	    goto next_insn;


	  if (peep2_current_count == 0)
	    break;


	  pos = peep2_buf_position (peep2_current + peep2_current_count);
	  peep2_insn_data[pos].insn = PEEP2_EOB;
	  COPY_REG_SET (peep2_insn_data[pos].live_before, live);


	  head = peep2_insn_data[peep2_current].insn;
	  attempt = peephole2_insns (PATTERN (head), head, &match_len);
	  if (attempt != NULL)
	    {
	      rtx last = peep2_attempt (bb, head, match_len, attempt);
	      if (last)
		{
		  peep2_update_life (bb, match_len, last, PREV_INSN (attempt));
		  continue;
		}
	    }


	  peep2_current = peep2_buf_position (peep2_current + 1);
	  peep2_current_count--;
	}
    }

  default_rtl_profile ();
  for (i = 0; i < MAX_INSNS_PER_PEEP2 + 1; ++i)
    BITMAP_FREE (peep2_insn_data[i].live_before);
  BITMAP_FREE (live);
  if (peep2_do_rebuild_jump_labels)
    rebuild_jump_labels (get_insns ());
}
