try_crossjump_bb (int mode, basic_block bb)
{
  edge e, e2, fallthru;
  bool changed;
  unsigned max, ix, ix2;
  basic_block ev, ev2;


  if (EDGE_COUNT (bb->preds) < 2)
    return false;


  if (optimize_bb_for_size_p (bb)
      && bb != EXIT_BLOCK_PTR
      && computed_jump_p (BB_END (bb)))
    return false;


  if (BB_PARTITION (EDGE_PRED (bb, 0)->src) !=
					BB_PARTITION (EDGE_PRED (bb, 1)->src)
      || (EDGE_PRED (bb, 0)->flags & EDGE_CROSSING))
    return false;


  fallthru = NULL;
  max = PARAM_VALUE (PARAM_MAX_CROSSJUMP_EDGES);

  if (EDGE_COUNT (bb->preds) > max)
    return false;

  fallthru = find_fallthru_edge (bb->preds);

  changed = false;
  for (ix = 0, ev = bb; ix < EDGE_COUNT (ev->preds); )
    {
      e = EDGE_PRED (ev, ix);
      ix++;


      if (fallthru)
	{


	  if (e == fallthru)
	    continue;


	  if (!first_pass
	      && !((e->src->flags & BB_MODIFIED)
		   || (fallthru->src->flags & BB_MODIFIED)))
	    continue;

	  if (try_crossjump_to_edge (mode, e, fallthru))
	    {
	      changed = true;
	      ix = 0;
	      ev = bb;
	      continue;
	    }
	}


      if (EDGE_SUCC (e->src, 0) != e)
	continue;

      for (ix2 = 0, ev2 = bb; ix2 < EDGE_COUNT (ev2->preds); )
	{
	  e2 = EDGE_PRED (ev2, ix2);
	  ix2++;

	  if (e2 == e)
	    continue;


	  if (e2 == fallthru)
	    continue;


	  if (e->src->index > e2->src->index)
	    continue;


	  if (!first_pass
	      && !((e->src->flags & BB_MODIFIED)
		   || (e2->src->flags & BB_MODIFIED)))
	    continue;

	  if (try_crossjump_to_edge (mode, e, e2))
	    {
	      changed = true;
	      ev2 = bb;
	      ix = 0;
	      break;
	    }
	}
    }

  if (changed)
    crossjumps_occured = true;

  return changed;
}
