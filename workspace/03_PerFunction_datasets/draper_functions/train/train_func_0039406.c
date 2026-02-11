build_insn_chain (first)
     rtx first;
{
  struct insn_chain **p = &reload_insn_chain;
  struct insn_chain *prev = 0;
  basic_block b = ENTRY_BLOCK_PTR->next_bb;
  regset_head live_relevant_regs_head;

  live_relevant_regs = INITIALIZE_REG_SET (live_relevant_regs_head);

  for (; first; first = NEXT_INSN (first))
    {
      struct insn_chain *c;

      if (first == b->head)
	{
	  int i;

	  CLEAR_REG_SET (live_relevant_regs);

	  EXECUTE_IF_SET_IN_BITMAP
	    (b->global_live_at_start, 0, i,
	     {
	       if (i < FIRST_PSEUDO_REGISTER
		   ? ! TEST_HARD_REG_BIT (eliminable_regset, i)
		   : reg_renumber[i] >= 0)
		 SET_REGNO_REG_SET (live_relevant_regs, i);
	     });
	}

      if (GET_CODE (first) != NOTE && GET_CODE (first) != BARRIER)
	{
	  c = new_insn_chain ();
	  c->prev = prev;
	  prev = c;
	  *p = c;
	  p = &c->next;
	  c->insn = first;
	  c->block = b->index;

	  if (INSN_P (first))
	    {
	      rtx link;


	      for (link = REG_NOTES (first); link; link = XEXP (link, 1))
		if (REG_NOTE_KIND (link) == REG_DEAD
		    && GET_CODE (XEXP (link, 0)) == REG)
		  reg_dies (REGNO (XEXP (link, 0)), GET_MODE (XEXP (link, 0)),
			    c);

	      COPY_REG_SET (&c->live_throughout, live_relevant_regs);


	      note_stores (PATTERN (first), reg_becomes_live,
			   &c->dead_or_set);
	    }
	  else
	    COPY_REG_SET (&c->live_throughout, live_relevant_regs);

	  if (INSN_P (first))
	    {
	      rtx link;


	      for (link = REG_NOTES (first); link; link = XEXP (link, 1))
		if (REG_NOTE_KIND (link) == REG_UNUSED
		    && GET_CODE (XEXP (link, 0)) == REG)
		  reg_dies (REGNO (XEXP (link, 0)), GET_MODE (XEXP (link, 0)),
			    c);
	    }
	}

      if (first == b->end)
	b = b->next_bb;


      if (b == EXIT_BLOCK_PTR)
	{
	  for (first = NEXT_INSN (first) ; first; first = NEXT_INSN (first))
	    if (INSN_P (first)
		&& GET_CODE (PATTERN (first)) != USE
		&& ! ((GET_CODE (PATTERN (first)) == ADDR_VEC
		       || GET_CODE (PATTERN (first)) == ADDR_DIFF_VEC)
		      && prev_real_insn (first) != 0
		      && GET_CODE (prev_real_insn (first)) == JUMP_INSN))
	      abort ();
	  break;
	}
    }
  FREE_REG_SET (live_relevant_regs);
  *p = 0;
}
