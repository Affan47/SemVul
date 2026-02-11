df_find_hard_reg_defs (rtx x, HARD_REG_SET *defs)
{
  RTX_CODE code = GET_CODE (x);
  int i;

  switch (code)
    {
    case SET:
      df_find_hard_reg_defs_1 (SET_DEST (x), defs);
      break;

    case CLOBBER:
      df_find_hard_reg_defs_1 (XEXP (x, 0), defs);
      break;

    case COND_EXEC:
      df_find_hard_reg_defs (COND_EXEC_CODE (x), defs);
      break;

    case PARALLEL:
      for (i = 0; i < XVECLEN (x, 0); i++)
	df_find_hard_reg_defs (XVECEXP (x, 0, i), defs);
      break;
    default:

      break;
    }
}
