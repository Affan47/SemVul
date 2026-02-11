if_convertible_bb_p (struct loop *loop, basic_block bb, basic_block exit_bb)
{
  edge e;
  edge_iterator ei;

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "----------[%d]-------------\n", bb->index);

  if (EDGE_COUNT (bb->preds) > 2
      || EDGE_COUNT (bb->succs) > 2)
    return false;

  if (exit_bb)
    {
      if (bb != loop->latch)
	{
	  if (dump_file && (dump_flags & TDF_DETAILS))
	    fprintf (dump_file, "basic block after exit bb but before latch\n");
	  return false;
	}
      else if (!empty_block_p (bb))
	{
	  if (dump_file && (dump_flags & TDF_DETAILS))
	    fprintf (dump_file, "non empty basic block after exit bb\n");
	  return false;
	}
      else if (bb == loop->latch
	       && bb != exit_bb
	       && !dominated_by_p (CDI_DOMINATORS, bb, exit_bb))
	  {
	    if (dump_file && (dump_flags & TDF_DETAILS))
	      fprintf (dump_file, "latch is not dominated by exit_block\n");
	    return false;
	  }
    }


  FOR_EACH_EDGE (e, ei, bb->succs)
    if (e->flags &
	(EDGE_ABNORMAL_CALL | EDGE_EH | EDGE_ABNORMAL | EDGE_IRREDUCIBLE_LOOP))
      {
	if (dump_file && (dump_flags & TDF_DETAILS))
	  fprintf (dump_file, "Difficult to handle edges\n");
	return false;
      }

  if (EDGE_COUNT (bb->preds) == 2
      && bb != loop->header
      && !bb_postdominates_preds (bb))
    return false;

  return true;
}
