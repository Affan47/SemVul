rewrite_into_loop_closed_ssa (bitmap changed_bbs, unsigned update_flag)
{
  bitmap loop_exits;
  bitmap *use_blocks;
  unsigned i, old_num_ssa_names;
  bitmap names_to_rename;

  loops_state_set (LOOP_CLOSED_SSA);
  if (number_of_loops () <= 1)
    return;

  loop_exits = get_loops_exits ();
  names_to_rename = BITMAP_ALLOC (NULL);


  update_ssa (update_flag);

  old_num_ssa_names = num_ssa_names;
  use_blocks = XCNEWVEC (bitmap, old_num_ssa_names);


  find_uses_to_rename (changed_bbs, use_blocks, names_to_rename);


  add_exit_phis (names_to_rename, use_blocks, loop_exits);

  for (i = 0; i < old_num_ssa_names; i++)
    BITMAP_FREE (use_blocks[i]);
  free (use_blocks);
  BITMAP_FREE (loop_exits);
  BITMAP_FREE (names_to_rename);


  update_ssa (TODO_update_ssa);
}
