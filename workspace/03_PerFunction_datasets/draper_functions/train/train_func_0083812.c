for_each_insn_in_loop (loop, fncall)
     struct loop *loop;
     loop_insn_callback fncall;
{
  int not_every_iteration = 0;
  int maybe_multiple = 0;
  int past_loop_latch = 0;
  int loop_depth = 0;
  rtx p;


  if (prev_nonnote_insn (loop->scan_start) != prev_nonnote_insn (loop->start))
    maybe_multiple = back_branch_in_range_p (loop, loop->scan_start);


  for (p = next_insn_in_loop (loop, loop->scan_start);
       p != NULL_RTX;
       p = next_insn_in_loop (loop, p))
    {
      p = fncall (loop, p, not_every_iteration, maybe_multiple);


      if (GET_CODE (p) == CODE_LABEL)
	{
	  rtx insn = p;

	  maybe_multiple = 0;

	  while (1)
	    {
	      insn = NEXT_INSN (insn);
	      if (insn == loop->scan_start)
		break;
	      if (insn == loop->end)
		{
		  if (loop->top != 0)
		    insn = loop->top;
		  else
		    break;
		  if (insn == loop->scan_start)
		    break;
		}

	      if (GET_CODE (insn) == JUMP_INSN
		  && GET_CODE (PATTERN (insn)) != RETURN
		  && (!any_condjump_p (insn)
		      || (JUMP_LABEL (insn) != 0
			  && JUMP_LABEL (insn) != loop->scan_start
			  && !loop_insn_first_p (p, JUMP_LABEL (insn)))))
		{
		  maybe_multiple = 1;
		  break;
		}
	    }
	}


      if (GET_CODE (p) == JUMP_INSN


	  && !(JUMP_LABEL (p) == loop->top
	       && ((NEXT_INSN (NEXT_INSN (p)) == loop->end
		    && any_uncondjump_p (p))
		   || (NEXT_INSN (p) == loop->end && any_condjump_p (p)))))
	{
	  rtx label = 0;


	  for (label = loop->exit_labels; label; label = LABEL_NEXTREF (label))
	    if (XEXP (label, 0) == JUMP_LABEL (p))
	      break;

	  if (!label)
	    not_every_iteration = 1;
	}

      else if (GET_CODE (p) == NOTE)
	{


	  if ((NOTE_LINE_NUMBER (p) == NOTE_INSN_LOOP_VTOP
	       || NOTE_LINE_NUMBER (p) == NOTE_INSN_LOOP_CONT)
	      && loop_depth == 0)
	    not_every_iteration = 0;
	  else if (NOTE_LINE_NUMBER (p) == NOTE_INSN_LOOP_BEG)
	    loop_depth++;
	  else if (NOTE_LINE_NUMBER (p) == NOTE_INSN_LOOP_END)
	    loop_depth--;
	}


      if (GET_CODE (p) == JUMP_INSN
	  && JUMP_LABEL (p) == NEXT_INSN (loop->start))
	past_loop_latch = 1;


      if (not_every_iteration
	  && !past_loop_latch
	  && GET_CODE (p) == CODE_LABEL
	  && no_labels_between_p (p, loop->end)
	  && loop_insn_first_p (p, loop->cont))
	not_every_iteration = 0;
    }
}
