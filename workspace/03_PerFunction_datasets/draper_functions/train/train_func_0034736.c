layout_superblocks ()
{
  basic_block end = ENTRY_BLOCK_PTR->succ->dest;
  basic_block bb = ENTRY_BLOCK_PTR->succ->dest->next_bb;

  while (bb != EXIT_BLOCK_PTR)
    {
      edge e, best = NULL;
      while (RBI (end)->next)
	end = RBI (end)->next;

      for (e = end->succ; e; e = e->succ_next)
	if (e->dest != EXIT_BLOCK_PTR
	    && e->dest != ENTRY_BLOCK_PTR->succ->dest
	    && !RBI (e->dest)->visited
	    && (!best || EDGE_FREQUENCY (e) > EDGE_FREQUENCY (best)))
	  best = e;

      if (best)
	{
	  RBI (end)->next = best->dest;
	  RBI (best->dest)->visited = 1;
	}
      else
	for (; bb != EXIT_BLOCK_PTR; bb=bb->next_bb)
	  {
	    if (!RBI (bb)->visited)
	      {
		RBI (end)->next = bb;
		RBI (bb)->visited = 1;
		break;
	      }
	  }
    }
}
