find_many_sub_basic_blocks (blocks)
     sbitmap blocks;
{
  basic_block bb, min, max;

  FOR_EACH_BB (bb)
    SET_STATE (bb,
	       TEST_BIT (blocks, bb->index) ? BLOCK_TO_SPLIT : BLOCK_ORIGINAL);

  FOR_EACH_BB (bb)
    if (STATE (bb) == BLOCK_TO_SPLIT)
      find_bb_boundaries (bb);

  FOR_EACH_BB (bb)
    if (STATE (bb) != BLOCK_ORIGINAL)
      break;

  min = max = bb;
  for (; bb != EXIT_BLOCK_PTR; bb = bb->next_bb)
    if (STATE (bb) != BLOCK_ORIGINAL)
      max = bb;


  make_edges (NULL, min, max, 1);


  FOR_BB_BETWEEN (bb, min, max->next_bb, next_bb)
    {
      edge e;

      if (STATE (bb) == BLOCK_ORIGINAL)
	continue;
      if (STATE (bb) == BLOCK_NEW)
	{
	  bb->count = 0;
	  bb->frequency = 0;
	  for (e = bb->pred; e; e=e->pred_next)
	    {
	      bb->count += e->count;
	      bb->frequency += EDGE_FREQUENCY (e);
	    }
	}

      compute_outgoing_frequencies (bb);
    }

  FOR_EACH_BB (bb)
    SET_STATE (bb, 0);
}
