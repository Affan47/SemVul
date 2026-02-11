discover_loops (bitmap_obstack *stack, struct hw_doloop_hooks *hooks)
{
  hwloop_info loops = NULL;
  hwloop_info loop;
  basic_block bb;
  int nloops = 0;


  FOR_EACH_BB (bb)
    {
      rtx tail = BB_END (bb);
      rtx insn, reg;

      while (tail && GET_CODE (tail) == NOTE && tail != BB_HEAD (bb))
	tail = PREV_INSN (tail);

      if (tail == NULL_RTX)
	continue;

      if (!JUMP_P (tail))
	continue;
      reg = hooks->end_pattern_reg (tail);
      if (reg == NULL_RTX)
	continue;


      insn = JUMP_LABEL (tail);
      while (insn && !NONDEBUG_INSN_P (insn))
	insn = NEXT_INSN (insn);
      if (insn == tail)
	{
	  basic_block succ = FALLTHRU_EDGE (bb)->dest;
	  if (dump_file)
	    {
	      fprintf (dump_file, ";; degenerate loop ending at\n");
	      print_rtl_single (dump_file, tail);
	    }
	  if (!REGNO_REG_SET_P (df_get_live_in (succ), REGNO (reg)))
	    {
	      if (dump_file)
		fprintf (dump_file, ";; deleting it\n");
	      delete_insn_and_edges (tail);
	      continue;
	    }
	}

      loop = XCNEW (struct hwloop_info_d);
      loop->next = loops;
      loops = loop;
      loop->loop_no = nloops++;
      loop->blocks = VEC_alloc (basic_block, heap, 20);
      loop->block_bitmap = BITMAP_ALLOC (stack);

      if (dump_file)
	{
	  fprintf (dump_file, ";; potential loop %d ending at\n",
		   loop->loop_no);
	  print_rtl_single (dump_file, tail);
	}

      discover_loop (loop, bb, tail, reg);
    }


  for (loop = loops; loop; loop = loop->next)
    {
      hwloop_info other;

      if (loop->bad)
	continue;

      for (other = loops; other; other = other->next)
	{
	  if (other->bad)
	    continue;

	  if (!bitmap_intersect_p (other->block_bitmap, loop->block_bitmap))
	    continue;
	  if (!bitmap_intersect_compl_p (other->block_bitmap,
					 loop->block_bitmap))
	    VEC_safe_push (hwloop_info, heap, loop->loops, other);
	  else if (!bitmap_intersect_compl_p (loop->block_bitmap,
					      other->block_bitmap))
	    VEC_safe_push (hwloop_info, heap, other->loops, loop);
	  else
	    {
	      if (dump_file)
		fprintf (dump_file,
			 ";; can't find suitable nesting for loops %d and %d\n",
			 loop->loop_no, other->loop_no);
	      loop->bad = other->bad = true;
	    }
	}
    }

  if (dump_file)
    dump_hwloops (loops);

  return loops;
}
