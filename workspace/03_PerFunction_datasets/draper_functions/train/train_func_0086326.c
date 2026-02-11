haifa_classify_rtx (const_rtx x)
{
  int tmp_class = TRAP_FREE;
  int insn_class = TRAP_FREE;
  enum rtx_code code;

  if (GET_CODE (x) == PARALLEL)
    {
      int i, len = XVECLEN (x, 0);

      for (i = len - 1; i >= 0; i--)
	{
	  tmp_class = haifa_classify_rtx (XVECEXP (x, 0, i));
	  insn_class = WORST_CLASS (insn_class, tmp_class);
	  if (insn_class == TRAP_RISKY || insn_class == IRISKY)
	    break;
	}
    }
  else
    {
      code = GET_CODE (x);
      switch (code)
	{
	case CLOBBER:

	  tmp_class = may_trap_exp (XEXP (x, 0), 1);
	  break;
	case SET:

	  tmp_class = may_trap_exp (SET_DEST (x), 1);
	  if (tmp_class == TRAP_RISKY)
	    break;

	  tmp_class =
	    WORST_CLASS (tmp_class,
			 may_trap_exp (SET_SRC (x), 0));
	  break;
	case COND_EXEC:
	  tmp_class = haifa_classify_rtx (COND_EXEC_CODE (x));
	  if (tmp_class == TRAP_RISKY)
	    break;
	  tmp_class = WORST_CLASS (tmp_class,
				   may_trap_exp (COND_EXEC_TEST (x), 0));
	  break;
	case TRAP_IF:
	  tmp_class = TRAP_RISKY;
	  break;
	default:;
	}
      insn_class = tmp_class;
    }

  return insn_class;
}
