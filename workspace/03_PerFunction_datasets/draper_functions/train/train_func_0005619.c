dead_libcall_p (rtx insn, int *counts)
{
  rtx note, set, new;


  note = find_reg_note (insn, REG_EQUAL, NULL_RTX);
  if (!note)
    return false;

  set = single_set (insn);
  if (!set)
    return false;

  new = simplify_rtx (XEXP (note, 0));
  if (!new)
    new = XEXP (note, 0);


  count_reg_usage (insn, counts, -1);

  if (validate_change (insn, &SET_SRC (set), new, 0))
    {
      count_reg_usage (insn, counts, 1);
      remove_note (insn, find_reg_note (insn, REG_RETVAL, NULL_RTX));
      remove_note (insn, note);
      return true;
    }

  if (CONSTANT_P (new))
    {
      new = force_const_mem (GET_MODE (SET_DEST (set)), new);
      if (new && validate_change (insn, &SET_SRC (set), new, 0))
	{
	  count_reg_usage (insn, counts, 1);
	  remove_note (insn, find_reg_note (insn, REG_RETVAL, NULL_RTX));
	  remove_note (insn, note);
	  return true;
	}
    }

  count_reg_usage (insn, counts, 1);
  return false;
}
