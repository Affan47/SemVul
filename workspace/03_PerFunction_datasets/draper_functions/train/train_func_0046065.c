mark_used_regs_combine (rtx x)
{
  RTX_CODE code = GET_CODE (x);
  unsigned int regno;
  int i;

  switch (code)
    {
    case LABEL_REF:
    case SYMBOL_REF:
    case CONST_INT:
    case CONST:
    case CONST_DOUBLE:
    case CONST_VECTOR:
    case PC:
    case ADDR_VEC:
    case ADDR_DIFF_VEC:
    case ASM_INPUT:
#ifdef HAVE_cc0


    case CC0:
#endif
      return;

    case CLOBBER:


      if (GET_CODE (XEXP (x, 0)) == MEM)
	mark_used_regs_combine (XEXP (XEXP (x, 0), 0));
      return;

    case REG:
      regno = REGNO (x);


      if (regno < FIRST_PSEUDO_REGISTER)
	{
	  unsigned int endregno, r;


	  if (regno == STACK_POINTER_REGNUM
#if FRAME_POINTER_REGNUM != HARD_FRAME_POINTER_REGNUM
	      || regno == HARD_FRAME_POINTER_REGNUM
#endif
#if FRAME_POINTER_REGNUM != ARG_POINTER_REGNUM
	      || (regno == ARG_POINTER_REGNUM && fixed_regs[regno])
#endif
	      || regno == FRAME_POINTER_REGNUM)
	    return;

	  endregno = regno + HARD_REGNO_NREGS (regno, GET_MODE (x));
	  for (r = regno; r < endregno; r++)
	    SET_HARD_REG_BIT (newpat_used_regs, r);
	}
      return;

    case SET:
      {


	rtx testreg = SET_DEST (x);

	while (GET_CODE (testreg) == SUBREG
	       || GET_CODE (testreg) == ZERO_EXTRACT
	       || GET_CODE (testreg) == SIGN_EXTRACT
	       || GET_CODE (testreg) == STRICT_LOW_PART)
	  testreg = XEXP (testreg, 0);

	if (GET_CODE (testreg) == MEM)
	  mark_used_regs_combine (XEXP (testreg, 0));

	mark_used_regs_combine (SET_SRC (x));
      }
      return;

    default:
      break;
    }


  {
    const char *fmt = GET_RTX_FORMAT (code);

    for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
      {
	if (fmt[i] == 'e')
	  mark_used_regs_combine (XEXP (x, i));
	else if (fmt[i] == 'E')
	  {
	    int j;

	    for (j = 0; j < XVECLEN (x, i); j++)
	      mark_used_regs_combine (XVECEXP (x, i, j));
	  }
      }
  }
}
