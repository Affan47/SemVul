convert_jumps_to_returns (basic_block last_bb, bool simple_p,
			  vec<edge> unconverted ATTRIBUTE_UNUSED)
{
  int i;
  basic_block bb;
  rtx label;
  edge_iterator ei;
  edge e;
  vec<basic_block> src_bbs;

  src_bbs.create (EDGE_COUNT (last_bb->preds));
  FOR_EACH_EDGE (e, ei, last_bb->preds)
    if (e->src != ENTRY_BLOCK_PTR)
      src_bbs.quick_push (e->src);

  label = BB_HEAD (last_bb);

  FOR_EACH_VEC_ELT (src_bbs, i, bb)
    {
      rtx jump = BB_END (bb);

      if (!JUMP_P (jump) || JUMP_LABEL (jump) != label)
	continue;

      e = find_edge (bb, last_bb);


      if (simplejump_p (jump))
	{


	  emit_use_return_register_into_block (bb);

	  emit_return_into_block (simple_p, bb);
	  delete_insn (jump);
	}


      else if (condjump_p (jump))
	{
	  rtx dest;

	  if (simple_p)
	    dest = simple_return_rtx;
	  else
	    dest = ret_rtx;
	  if (!redirect_jump (jump, dest, 0))
	    {
#ifdef HAVE_simple_return
	      if (simple_p)
		{
		  if (dump_file)
		    fprintf (dump_file,
			     "Failed to redirect bb %d branch.\n", bb->index);
		  unconverted.safe_push (e);
		}
#endif
	      continue;
	    }


	  emit_use_return_register_into_block (bb);


	  if (single_succ_p (bb))
	    continue;
	}
      else
	{
#ifdef HAVE_simple_return
	  if (simple_p)
	    {
	      if (dump_file)
		fprintf (dump_file,
			 "Failed to redirect bb %d branch.\n", bb->index);
	      unconverted.safe_push (e);
	    }
#endif
	  continue;
	}


      redirect_edge_succ (e, EXIT_BLOCK_PTR);
      e->flags &= ~EDGE_CROSSING;
    }
  src_bbs.release ();
  return unconverted;
}
