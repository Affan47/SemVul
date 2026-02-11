purge_all_dead_edges (int update_life_p)
{
  int purged = false;
  sbitmap blocks = 0;
  basic_block bb;

  if (update_life_p)
    {
      blocks = sbitmap_alloc (last_basic_block);
      sbitmap_zero (blocks);
    }

  FOR_EACH_BB (bb)
    {
      bool purged_here = purge_dead_edges (bb);

      purged |= purged_here;
      if (purged_here && update_life_p)
	SET_BIT (blocks, bb->index);
    }

  if (update_life_p && purged)
    update_life_info (blocks, UPDATE_LIFE_GLOBAL,
		      PROP_DEATH_NOTES | PROP_SCAN_DEAD_CODE
		      | PROP_KILL_DEAD_CODE);

  if (update_life_p)
    sbitmap_free (blocks);
  return purged;
}
