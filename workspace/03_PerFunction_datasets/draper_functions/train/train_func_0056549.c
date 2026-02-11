commit_one_edge_insertion (edge e, int watch_calls)
{
  rtx before = NULL_RTX, after = NULL_RTX, insns, tmp, last;
  basic_block bb = NULL;


  insns = e->insns;
  e->insns = NULL_RTX;


  if (watch_calls && (e->flags & EDGE_FALLTHRU) && !e->dest->pred->pred_next
      && e->src != ENTRY_BLOCK_PTR
      && GET_CODE (BB_END (e->src)) == CALL_INSN)
    {
      rtx next = next_nonnote_insn (BB_END (e->src));

      after = BB_HEAD (e->dest);

      while (next
	     && keep_with_call_p (next))
	{
	  after = next;
	  next = next_nonnote_insn (next);
	}
      bb = e->dest;
    }
  if (!before && !after)
    {


      if (e->dest->pred->pred_next == NULL && e->dest != EXIT_BLOCK_PTR)
	{
	  bb = e->dest;


	  tmp = BB_HEAD (bb);
	  if (GET_CODE (tmp) == CODE_LABEL)
	    tmp = NEXT_INSN (tmp);
	  if (NOTE_INSN_BASIC_BLOCK_P (tmp))
	    tmp = NEXT_INSN (tmp);
	  if (tmp == BB_HEAD (bb))
	    before = tmp;
	  else if (tmp)
	    after = PREV_INSN (tmp);
	  else
	    after = get_last_insn ();
	}


      else if ((e->flags & EDGE_ABNORMAL) == 0
	       && e->src->succ->succ_next == NULL
	       && e->src != ENTRY_BLOCK_PTR)
	{
	  bb = e->src;


	  if (GET_CODE (BB_END (bb)) == JUMP_INSN)
	    for (before = BB_END (bb);
		 GET_CODE (PREV_INSN (before)) == NOTE
		 && NOTE_LINE_NUMBER (PREV_INSN (before)) ==
		 NOTE_INSN_LOOP_BEG; before = PREV_INSN (before))
	      ;
	  else
	    {

	      if ((e->flags & EDGE_FALLTHRU) == 0)
		abort ();

	      after = BB_END (bb);
	    }
	}

      else
	{
	  bb = split_edge (e);
	  after = BB_END (bb);
	}
    }


  if (before)
    {
      emit_insn_before_noloc (insns, before);
      last = prev_nonnote_insn (before);
    }
  else
    last = emit_insn_after_noloc (insns, after);

  if (returnjump_p (last))
    {


      e = bb->succ;
      if (e->dest != EXIT_BLOCK_PTR
	  || e->succ_next != NULL || (e->flags & EDGE_FALLTHRU) == 0)
	abort ();

      e->flags &= ~EDGE_FALLTHRU;
      emit_barrier_after (last);

      if (before)
	delete_insn (before);
    }
  else if (GET_CODE (last) == JUMP_INSN)
    abort ();


  bb->aux = &bb->aux;
}
