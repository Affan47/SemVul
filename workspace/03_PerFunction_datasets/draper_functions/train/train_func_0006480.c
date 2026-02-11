cleanup_tree_cfg_1 (void)
{
  bool retval = false;
  basic_block bb;
  unsigned i, n;

  retval |= split_bbs_on_noreturn_calls ();


  cfgcleanup_altered_bbs = BITMAP_ALLOC (NULL);


  start_recording_case_labels ();


  n = last_basic_block;
  for (i = NUM_FIXED_BLOCKS; i < n; i++)
    {
      bb = BASIC_BLOCK (i);
      if (bb)
	retval |= cleanup_tree_cfg_bb (bb);
    }


  while (!bitmap_empty_p (cfgcleanup_altered_bbs))
    {
      i = bitmap_first_set_bit (cfgcleanup_altered_bbs);
      bitmap_clear_bit (cfgcleanup_altered_bbs, i);
      if (i < NUM_FIXED_BLOCKS)
	continue;

      bb = BASIC_BLOCK (i);
      if (!bb)
	continue;

      retval |= cleanup_tree_cfg_bb (bb);


      retval |= split_bbs_on_noreturn_calls ();
    }

  end_recording_case_labels ();
  BITMAP_FREE (cfgcleanup_altered_bbs);
  return retval;
}
