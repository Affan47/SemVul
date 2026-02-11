flow_call_edges_add (blocks)
     sbitmap blocks;
{
  int i;
  int blocks_split = 0;
  int last_bb = last_basic_block;
  bool check_last_block = false;

  if (n_basic_blocks == 0)
    return 0;

  if (! blocks)
    check_last_block = true;
  else
    check_last_block = TEST_BIT (blocks, EXIT_BLOCK_PTR->prev_bb->index);


  if (check_last_block)
    {
      basic_block bb = EXIT_BLOCK_PTR->prev_bb;
      rtx insn = bb->end;


      while (insn != bb->head
	     && keep_with_call_p (insn))
	insn = PREV_INSN (insn);

      if (need_fake_edge_p (insn))
	{
	  edge e;

	  for (e = bb->succ; e; e = e->succ_next)
	    if (e->dest == EXIT_BLOCK_PTR)
	      {
		insert_insn_on_edge (gen_rtx_USE (VOIDmode, const0_rtx), e);
		commit_edge_insertions ();
		break;
	      }
	}
    }


  for (i = 0; i < last_bb; i++)
    {
      basic_block bb = BASIC_BLOCK (i);
      rtx insn;
      rtx prev_insn;

      if (!bb)
	continue;

      if (blocks && !TEST_BIT (blocks, i))
	continue;

      for (insn = bb->end; ; insn = prev_insn)
	{
	  prev_insn = PREV_INSN (insn);
	  if (need_fake_edge_p (insn))
	    {
	      edge e;
	      rtx split_at_insn = insn;


	      if (GET_CODE (insn) == CALL_INSN)
		while (split_at_insn != bb->end
		       && keep_with_call_p (NEXT_INSN (split_at_insn)))
		  split_at_insn = NEXT_INSN (split_at_insn);


#ifdef ENABLE_CHECKING
	      if (split_at_insn == bb->end)
		for (e = bb->succ; e; e = e->succ_next)
		  if (e->dest == EXIT_BLOCK_PTR)
		    abort ();
#endif


	      if (split_at_insn != bb->end)
		{
		  e = split_block (bb, split_at_insn);
		  if (e)
		    blocks_split++;
		}

	      make_edge (bb, EXIT_BLOCK_PTR, EDGE_FAKE);
	    }

	  if (insn == bb->head)
	    break;
	}
    }

  if (blocks_split)
    verify_flow_info ();

  return blocks_split;
}
