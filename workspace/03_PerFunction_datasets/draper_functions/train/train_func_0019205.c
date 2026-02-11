ira_emit (bool loops_p)
{
  basic_block bb;
  rtx insn;
  edge_iterator ei;
  edge e;
  ira_allocno_t a;
  ira_allocno_iterator ai;

  FOR_EACH_ALLOCNO (a, ai)
    ALLOCNO_EMIT_DATA (a)->reg = regno_reg_rtx[ALLOCNO_REGNO (a)];
  if (! loops_p)
    return;
  at_bb_start = (move_t *) ira_allocate (sizeof (move_t) * last_basic_block);
  memset (at_bb_start, 0, sizeof (move_t) * last_basic_block);
  at_bb_end = (move_t *) ira_allocate (sizeof (move_t) * last_basic_block);
  memset (at_bb_end, 0, sizeof (move_t) * last_basic_block);
  local_allocno_bitmap = ira_allocate_bitmap ();
  used_regno_bitmap = ira_allocate_bitmap ();
  renamed_regno_bitmap = ira_allocate_bitmap ();
  max_regno_before_changing = max_reg_num ();
  ira_traverse_loop_tree (true, ira_loop_tree_root, change_loop, NULL);
  set_allocno_somewhere_renamed_p ();
  ira_free_bitmap (used_regno_bitmap);
  ira_free_bitmap (renamed_regno_bitmap);
  ira_free_bitmap (local_allocno_bitmap);
  setup_entered_from_non_parent_p ();
  FOR_EACH_BB (bb)
    {
      at_bb_start[bb->index] = NULL;
      at_bb_end[bb->index] = NULL;
      FOR_EACH_EDGE (e, ei, bb->succs)
	if (e->dest != EXIT_BLOCK_PTR)
	  generate_edge_moves (e);
    }
  allocno_last_set
    = (move_t *) ira_allocate (sizeof (move_t) * max_reg_num ());
  allocno_last_set_check
    = (int *) ira_allocate (sizeof (int) * max_reg_num ());
  memset (allocno_last_set_check, 0, sizeof (int) * max_reg_num ());
  memset (hard_regno_last_set_check, 0, sizeof (hard_regno_last_set_check));
  curr_tick = 0;
  FOR_EACH_BB (bb)
    unify_moves (bb, true);
  FOR_EACH_BB (bb)
    unify_moves (bb, false);
  move_vec = VEC_alloc (move_t, heap, ira_allocnos_num);
  emit_moves ();
  add_ranges_and_copies ();

  FOR_EACH_BB (bb)
    {
      free_move_list (at_bb_start[bb->index]);
      free_move_list (at_bb_end[bb->index]);
      FOR_EACH_EDGE (e, ei, bb->succs)
	{
	  free_move_list ((move_t) e->aux);
	  e->aux = NULL;
	}
    }
  VEC_free (move_t, heap, move_vec);
  ira_free (allocno_last_set_check);
  ira_free (allocno_last_set);
  commit_edge_insertions ();


  FOR_EACH_BB (bb)
    FOR_BB_INSNS_REVERSE (bb, insn)
      if (INSN_P (insn))
	recog_memoized (insn);
  ira_free (at_bb_end);
  ira_free (at_bb_start);
}
