can_hoist_insn_p (rtx insn, rtx val, regset live)
{
  rtx pat = PATTERN (insn);
  int i;


  if (!single_set (insn))
    return false;


  if (GET_CODE (insn) == CALL_INSN)
    return false;


  if (find_reg_note (insn, REG_RETVAL, NULL_RTX))
    return false;
  switch (GET_CODE (pat))
    {
    case SET:
      if (!hoist_test_store (SET_DEST (pat), val, live))
	return false;
      break;
    case USE:

      return false;
      break;
    case CLOBBER:
      if (!hoist_test_store (XEXP (pat, 0), val, live))
	return false;
      break;
    case PARALLEL:
      for (i = 0; i < XVECLEN (pat, 0); i++)
	{
	  rtx x = XVECEXP (pat, 0, i);
	  switch (GET_CODE (x))
	    {
	    case SET:
	      if (!hoist_test_store (SET_DEST (x), val, live))
		return false;
	      break;
	    case USE:


	      return false;
	      break;
	    case CLOBBER:
	      if (!hoist_test_store (SET_DEST (x), val, live))
		return false;
	      break;
	    default:
	      break;
	    }
	}
      break;
    default:
      abort ();
    }
  return true;
}
