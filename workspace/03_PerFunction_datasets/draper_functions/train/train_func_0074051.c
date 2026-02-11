back_branch_in_range_p (const struct loop *loop, rtx insn)
{
  rtx p, q, target_insn;
  rtx loop_start = loop->start;
  rtx loop_end = loop->end;
  rtx orig_loop_end = loop->end;


  loop_end = prev_nonnote_insn (loop_end);
  if (GET_CODE (loop_end) == BARRIER)
    loop_end = PREV_INSN (loop_end);


  while (INSN_DELETED_P (insn))
    insn = NEXT_INSN (insn);


  if (insn == loop_end || insn == orig_loop_end)
    return 0;

  for (p = NEXT_INSN (insn); p != loop_end; p = NEXT_INSN (p))
    {
      if (GET_CODE (p) == JUMP_INSN)
	{
	  target_insn = JUMP_LABEL (p);


	  for (q = loop_start; q != insn; q = NEXT_INSN (q))
	    if (q == target_insn)
	      return 1;
	}
    }

  return 0;
}
