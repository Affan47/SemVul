hoist_insn_after (rtx insn, rtx after, rtx val, rtx new)
{
  rtx pat;
  int i;
  rtx note;

  insn = emit_copy_of_insn_after (insn, after);
  pat = PATTERN (insn);


  while ((note = find_reg_note (insn, REG_UNUSED, NULL_RTX)))
    remove_note (insn, note);


  while ((note = find_reg_note (insn, REG_EQUAL, NULL_RTX)))
    remove_note (insn, note);
  while ((note = find_reg_note (insn, REG_EQUIV, NULL_RTX)))
    remove_note (insn, note);


  while ((note = find_reg_note (insn, REG_DEAD, NULL_RTX)))
    remove_note (insn, note);
  switch (GET_CODE (pat))
    {
    case SET:
      hoist_update_store (insn, &SET_DEST (pat), val, new);
      break;
    case USE:
      break;
    case CLOBBER:
      hoist_update_store (insn, &XEXP (pat, 0), val, new);
      break;
    case PARALLEL:
      for (i = 0; i < XVECLEN (pat, 0); i++)
	{
	  rtx x = XVECEXP (pat, 0, i);
	  switch (GET_CODE (x))
	    {
	    case SET:
	      hoist_update_store (insn, &SET_DEST (x), val, new);
	      break;
	    case USE:
	      break;
	    case CLOBBER:
	      hoist_update_store (insn, &SET_DEST (x), val, new);
	      break;
	    default:
	      break;
	    }
	}
      break;
    default:
      abort ();
    }
  if (!apply_change_group ())
    abort ();

  return insn;
}
