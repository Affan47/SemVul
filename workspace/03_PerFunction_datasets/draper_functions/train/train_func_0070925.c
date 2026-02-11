sched_get_condition_with_rev_uncached (const_rtx insn, bool *rev)
{
  rtx pat = PATTERN (insn);
  rtx src;

  if (rev)
    *rev = false;

  if (GET_CODE (pat) == COND_EXEC)
    return COND_EXEC_TEST (pat);

  if (!any_condjump_p (insn) || !onlyjump_p (insn))
    return 0;

  src = SET_SRC (pc_set (insn));

  if (XEXP (src, 2) == pc_rtx)
    return XEXP (src, 0);
  else if (XEXP (src, 1) == pc_rtx)
    {
      rtx cond = XEXP (src, 0);
      enum rtx_code revcode = reversed_comparison_code (cond, insn);

      if (revcode == UNKNOWN)
	return 0;

      if (rev)
	*rev = true;
      return cond;
    }

  return 0;
}
