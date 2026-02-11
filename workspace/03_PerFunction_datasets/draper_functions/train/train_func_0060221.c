copyprop_hardreg_forward (void)
{
  struct value_data *all_vd;
  bool need_refresh;
  basic_block bb, bbp = 0;

  need_refresh = false;

  all_vd = xmalloc (sizeof (struct value_data) * last_basic_block);

  FOR_EACH_BB (bb)
    {


      if (bb->pred)
	for (bbp = bb; bbp && bbp != bb->pred->src; bbp = bbp->prev_bb);
      if (bb->pred
	  && ! bb->pred->pred_next
	  && ! (bb->pred->flags & (EDGE_ABNORMAL_CALL | EDGE_EH))
	  && bb->pred->src != ENTRY_BLOCK_PTR
	  && bbp)
	all_vd[bb->index] = all_vd[bb->pred->src->index];
      else
	init_value_data (all_vd + bb->index);

      if (copyprop_hardreg_forward_1 (bb, all_vd + bb->index))
	need_refresh = true;
    }

  if (need_refresh)
    {
      if (rtl_dump_file)
	fputs ("\n\n", rtl_dump_file);


      delete_noop_moves (get_insns ());
      update_life_info (NULL, UPDATE_LIFE_GLOBAL_RM_NOTES,
			PROP_DEATH_NOTES
			| PROP_SCAN_DEAD_CODE
			| PROP_KILL_DEAD_CODE);
    }

  free (all_vd);
}
