duplicate_block (basic_block bb, edge e, basic_block after)
{
  edge s, n;
  basic_block new_bb;
  gcov_type new_count = e ? e->count : 0;
  edge_iterator ei;

  if (!cfg_hooks->duplicate_block)
    internal_error ("%s does not support duplicate_block",
		    cfg_hooks->name);

  if (bb->count < new_count)
    new_count = bb->count;

  gcc_checking_assert (can_duplicate_block_p (bb));

  new_bb = cfg_hooks->duplicate_block (bb);
  if (after)
    move_block_after (new_bb, after);

  new_bb->flags = bb->flags;
  FOR_EACH_EDGE (s, ei, bb->succs)
    {


      n = unchecked_make_edge (new_bb, s->dest, s->flags);
      n->probability = s->probability;
      if (e && bb->count)
	{

	  n->count = s->count * (new_count * 10000 / bb->count) / 10000;
	  s->count -= n->count;
	}
      else
	n->count = s->count;
      n->aux = s->aux;
    }

  if (e)
    {
      new_bb->count = new_count;
      bb->count -= new_count;

      new_bb->frequency = EDGE_FREQUENCY (e);
      bb->frequency -= EDGE_FREQUENCY (e);

      redirect_edge_and_branch_force (e, new_bb);

      if (bb->count < 0)
	bb->count = 0;
      if (bb->frequency < 0)
	bb->frequency = 0;
    }
  else
    {
      new_bb->count = bb->count;
      new_bb->frequency = bb->frequency;
    }

  set_bb_original (new_bb, bb);
  set_bb_copy (bb, new_bb);


  if (current_loops != NULL)
    {
      struct loop *cloop = bb->loop_father;
      struct loop *copy = get_loop_copy (cloop);


      if (!copy
	  && cloop->header == bb)
	{
	  add_bb_to_loop (new_bb, loop_outer (cloop));
	  cloop->header = NULL;
	  cloop->latch = NULL;
	  loops_state_set (LOOPS_NEED_FIXUP);
	}
      else
	{
	  add_bb_to_loop (new_bb, copy ? copy : cloop);


	  if (!copy
	      && cloop->latch == bb)
	    {
	      cloop->latch = NULL;
	      loops_state_set (LOOPS_MAY_HAVE_MULTIPLE_LATCHES);
	    }
	}
    }

  return new_bb;
}
