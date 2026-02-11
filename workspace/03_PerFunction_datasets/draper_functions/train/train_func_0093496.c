mark_constants (rtx insn)
{
  if (!INSN_P (insn))
    return;


  if (GET_CODE (PATTERN (insn)) == SEQUENCE)
    {
      rtx seq = PATTERN (insn);
      int i, n = XVECLEN (seq, 0);
      for (i = 0; i < n; ++i)
	{
	  rtx subinsn = XVECEXP (seq, 0, i);
	  if (INSN_P (subinsn))
	    for_each_rtx (&PATTERN (subinsn), mark_constant, NULL);
	}
    }
  else
    for_each_rtx (&PATTERN (insn), mark_constant, NULL);
}
