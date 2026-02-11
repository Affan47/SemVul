loop_regs_update (loop, seq)
     const struct loop *loop ATTRIBUTE_UNUSED;
     rtx seq;
{
  rtx insn;


  if (seq == NULL_RTX)
    return;

  if (INSN_P (seq))
    {
      insn = seq;
      while (insn != NULL_RTX)
	{
	  rtx set = single_set (insn);

	  if (set && GET_CODE (SET_DEST (set)) == REG)
	    record_base_value (REGNO (SET_DEST (set)), SET_SRC (set), 0);

	  insn = NEXT_INSN (insn);
	}
    }
  else if (GET_CODE (seq) == SET
	   && GET_CODE (SET_DEST (seq)) == REG)
    record_base_value (REGNO (SET_DEST (seq)), SET_SRC (seq), 0);
}
