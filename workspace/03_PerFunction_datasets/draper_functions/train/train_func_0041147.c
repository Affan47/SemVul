max_operand_1 (rtx x)
{
  RTX_CODE code;
  int i;
  int len;
  const char *fmt;

  if (x == 0)
    return;

  code = GET_CODE (x);

  if (code == MATCH_OPERAND || code == MATCH_OPERATOR
      || code == MATCH_PARALLEL)
    max_opno = MAX (max_opno, XINT (x, 0));

  fmt = GET_RTX_FORMAT (code);
  len = GET_RTX_LENGTH (code);
  for (i = 0; i < len; i++)
    {
      if (fmt[i] == 'e' || fmt[i] == 'u')
	max_operand_1 (XEXP (x, i));
      else if (fmt[i] == 'E')
	{
	  int j;
	  for (j = 0; j < XVECLEN (x, i); j++)
	    max_operand_1 (XVECEXP (x, i, j));
	}
    }
}
