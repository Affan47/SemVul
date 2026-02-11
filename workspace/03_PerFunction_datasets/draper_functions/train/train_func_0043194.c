merge_blocks (basic_block a, basic_block b)
{
  edge e;
  edge_iterator ei;

  if (!cfg_hooks->merge_blocks)
    internal_error ("%s does not support merge_blocks", cfg_hooks->name);

  cfg_hooks->merge_blocks (a, b);

  if (current_loops != NULL)
    {

      if (a->loop_father->header == a)
	{


	  if (b->loop_father->header == b)
	    {
	      b->loop_father->header = NULL;
	      b->loop_father->latch = NULL;
	      loops_state_set (LOOPS_NEED_FIXUP);
	    }
	}


      else if (b->loop_father->header == b)
	{
	  remove_bb_from_loops (a);
	  add_bb_to_loop  (a, b->loop_father);
	  a->loop_father->header = a;
	}
      remove_bb_from_loops (b);
    }


  while (EDGE_COUNT (a->succs) != 0)
    remove_edge (EDGE_SUCC (a, 0));


  FOR_EACH_EDGE (e, ei, b->succs)
    {
      e->src = a;
      if (current_loops != NULL)
	{

	  if (e->dest->loop_father->latch == b)
	    e->dest->loop_father->latch = a;
	  rescan_loop_exit (e, true, false);
	}
    }
  a->succs = b->succs;
  a->flags |= b->flags;


  b->preds = b->succs = NULL;

  if (dom_info_available_p (CDI_DOMINATORS))
    redirect_immediate_dominators (CDI_DOMINATORS, b, a);

  if (dom_info_available_p (CDI_DOMINATORS))
    delete_from_dominance_info (CDI_DOMINATORS, b);
  if (dom_info_available_p (CDI_POST_DOMINATORS))
    delete_from_dominance_info (CDI_POST_DOMINATORS, b);

  expunge_block (b);
}
