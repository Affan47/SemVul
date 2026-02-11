execute_lower_resx (void)
{
  basic_block bb;
  struct pointer_map_t *mnt_map;
  bool dominance_invalidated = false;
  bool any_rewritten = false;

  mnt_map = pointer_map_create ();

  FOR_EACH_BB (bb)
    {
      gimple last = last_stmt (bb);
      if (last && is_gimple_resx (last))
	{
	  dominance_invalidated |= lower_resx (bb, last, mnt_map);
	  any_rewritten = true;
	}
    }

  pointer_map_destroy (mnt_map);

  if (dominance_invalidated)
    {
      free_dominance_info (CDI_DOMINATORS);
      free_dominance_info (CDI_POST_DOMINATORS);
    }

  return any_rewritten ? TODO_update_ssa_only_virtuals : 0;
}
