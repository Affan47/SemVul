block_at_edge_of_live_range_p (int bb, btr_def def)
{
  if (def->other_btr_uses_before_def && BASIC_BLOCK (bb) == def->bb)
    return 1;
  else if (def->other_btr_uses_after_use)
    {
      btr_user user;
      for (user = def->uses; user != NULL; user = user->next)
	if (BASIC_BLOCK (bb) == user->bb)
	  return 1;
    }
  return 0;
}
