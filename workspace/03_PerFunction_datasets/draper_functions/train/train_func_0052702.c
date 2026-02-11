store_killed_in_insn (rtx x, rtx x_regs, rtx insn, int after)
{
  rtx reg, base, note;

  if (!INSN_P (insn))
    return false;

  if (GET_CODE (insn) == CALL_INSN)
    {


      if (! CONST_OR_PURE_CALL_P (insn) || pure_call_p (insn))
	return true;


      for (reg = x_regs; reg; reg = XEXP (reg, 1))
	{
	  base = find_base_term (XEXP (reg, 0));
	  if (!base
	      || (GET_CODE (base) == ADDRESS
		  && GET_MODE (base) == Pmode
		  && XEXP (base, 0) == stack_pointer_rtx))
	    return true;
	}

      return false;
    }

  if (GET_CODE (PATTERN (insn)) == SET)
    {
      rtx pat = PATTERN (insn);
      rtx dest = SET_DEST (pat);

      if (GET_CODE (dest) == SIGN_EXTRACT
	  || GET_CODE (dest) == ZERO_EXTRACT)
	dest = XEXP (dest, 0);


      if (GET_CODE (dest) == MEM
	  && !expr_equiv_p (dest, x))
	{
	  if (after)
	    {
	      if (output_dependence (dest, x))
		return true;
	    }
	  else
	    {
	      if (output_dependence (x, dest))
		return true;
	    }
	}
      if (find_loads (SET_SRC (pat), x, after))
	return true;
    }
  else if (find_loads (PATTERN (insn), x, after))
    return true;


  note = find_reg_equal_equiv_note (insn);
  if (! note)
    return false;
  note = XEXP (note, 0);


  if (expr_equiv_p (note, x))
    return false;


  return find_loads (note, x, after);
}
