const_iteration_count (rtx count_reg, basic_block pre_header,
		       HOST_WIDEST_INT * count)
{
  rtx insn;
  rtx head, tail;

  if (! pre_header)
    return NULL_RTX;

  get_ebb_head_tail (pre_header, pre_header, &head, &tail);

  for (insn = tail; insn != PREV_INSN (head); insn = PREV_INSN (insn))
    if (NONDEBUG_INSN_P (insn) && single_set (insn) &&
	rtx_equal_p (count_reg, SET_DEST (single_set (insn))))
      {
	rtx pat = single_set (insn);

	if (CONST_INT_P (SET_SRC (pat)))
	  {
	    *count = INTVAL (SET_SRC (pat));
	    return insn;
	  }

	return NULL_RTX;
      }

  return NULL_RTX;
}
