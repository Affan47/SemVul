reg_referenced_p (const_rtx x, const_rtx body)
{
  int i;

  switch (GET_CODE (body))
    {
    case SET:
      if (reg_overlap_mentioned_p (x, SET_SRC (body)))
	return 1;


      if (GET_CODE (SET_DEST (body)) != CC0
	  && GET_CODE (SET_DEST (body)) != PC
	  && !REG_P (SET_DEST (body))
	  && ! (GET_CODE (SET_DEST (body)) == SUBREG
		&& REG_P (SUBREG_REG (SET_DEST (body)))
		&& (((GET_MODE_SIZE (GET_MODE (SUBREG_REG (SET_DEST (body))))
		      + (UNITS_PER_WORD - 1)) / UNITS_PER_WORD)
		    == ((GET_MODE_SIZE (GET_MODE (SET_DEST (body)))
			 + (UNITS_PER_WORD - 1)) / UNITS_PER_WORD)))
	  && reg_overlap_mentioned_p (x, SET_DEST (body)))
	return 1;
      return 0;

    case ASM_OPERANDS:
      for (i = ASM_OPERANDS_INPUT_LENGTH (body) - 1; i >= 0; i--)
	if (reg_overlap_mentioned_p (x, ASM_OPERANDS_INPUT (body, i)))
	  return 1;
      return 0;

    case CALL:
    case USE:
    case IF_THEN_ELSE:
      return reg_overlap_mentioned_p (x, body);

    case TRAP_IF:
      return reg_overlap_mentioned_p (x, TRAP_CONDITION (body));

    case PREFETCH:
      return reg_overlap_mentioned_p (x, XEXP (body, 0));

    case UNSPEC:
    case UNSPEC_VOLATILE:
      for (i = XVECLEN (body, 0) - 1; i >= 0; i--)
	if (reg_overlap_mentioned_p (x, XVECEXP (body, 0, i)))
	  return 1;
      return 0;

    case PARALLEL:
      for (i = XVECLEN (body, 0) - 1; i >= 0; i--)
	if (reg_referenced_p (x, XVECEXP (body, 0, i)))
	  return 1;
      return 0;

    case CLOBBER:
      if (MEM_P (XEXP (body, 0)))
	if (reg_overlap_mentioned_p (x, XEXP (XEXP (body, 0), 0)))
	  return 1;
      return 0;

    case COND_EXEC:
      if (reg_overlap_mentioned_p (x, COND_EXEC_TEST (body)))
	return 1;
      return reg_referenced_p (x, COND_EXEC_CODE (body));

    default:
      return 0;
    }
}
