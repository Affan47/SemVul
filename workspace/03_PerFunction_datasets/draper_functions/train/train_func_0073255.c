cleanup_barriers (void)
{
  rtx insn, next, prev;
  for (insn = get_insns (); insn; insn = next)
    {
      next = NEXT_INSN (insn);
      if (BARRIER_P (insn))
	{
	  prev = prev_nonnote_insn (insn);
	  if (!prev)
	    continue;
	  if (BARRIER_P (prev))
	    delete_insn (insn);
	  else if (prev != PREV_INSN (insn))
	    {
	      basic_block bb = BLOCK_FOR_INSN (prev);
	      rtx end = PREV_INSN (insn);
	      reorder_insns_nobb (insn, insn, prev);
	      if (bb)
		{


		  BB_END (bb) = prev;
		  do
		    {
		      prev = NEXT_INSN (prev);
		      if (prev != insn && BLOCK_FOR_INSN (prev) == bb)
			BLOCK_FOR_INSN (prev) = NULL;
		    }
		  while (prev != end);
		}
	    }
	}
    }
  return 0;
}
