merge_blocks_move (edge e, basic_block b, basic_block c, int mode)
{
  basic_block next;


  if (BB_PARTITION (b) != BB_PARTITION (c))
    return NULL;


  if (e->flags & EDGE_FALLTHRU)
    {
      int b_index = b->index, c_index = c->index;
      merge_blocks (b, c);
      update_forwarder_flag (b);

      if (dump_file)
	fprintf (dump_file, "Merged %d and %d without moving.\n",
		 b_index, c_index);

      return b->prev_bb == ENTRY_BLOCK_PTR ? b : b->prev_bb;
    }


  else if (mode & CLEANUP_EXPENSIVE)
    {
      edge tmp_edge, b_fallthru_edge;
      bool c_has_outgoing_fallthru;
      bool b_has_incoming_fallthru;


      if (FORWARDER_BLOCK_P (b) || FORWARDER_BLOCK_P (c))
	return NULL;


      tmp_edge = find_fallthru_edge (c->succs);
      c_has_outgoing_fallthru = (tmp_edge != NULL);

      tmp_edge = find_fallthru_edge (b->preds);
      b_has_incoming_fallthru = (tmp_edge != NULL);
      b_fallthru_edge = tmp_edge;
      next = b->prev_bb;
      if (next == c)
	next = next->prev_bb;


      if (! c_has_outgoing_fallthru)
	{
	  merge_blocks_move_successor_nojumps (b, c);
	  return next == ENTRY_BLOCK_PTR ? next->next_bb : next;
	}


      if (b_has_incoming_fallthru)
	{
	  basic_block bb;

	  if (b_fallthru_edge->src == ENTRY_BLOCK_PTR)
	    return NULL;
	  bb = force_nonfallthru (b_fallthru_edge);
	  if (bb)
	    notice_new_block (bb);
	}

      merge_blocks_move_predecessor_nojumps (b, c);
      return next == ENTRY_BLOCK_PTR ? next->next_bb : next;
    }

  return NULL;
}
