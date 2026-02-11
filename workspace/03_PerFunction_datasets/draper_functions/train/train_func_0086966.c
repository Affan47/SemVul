check_asm_operands (rtx x)
{
  int noperands;
  rtx *operands;
  const char **constraints;
  int i;

  if (!asm_labels_ok (x))
    return 0;


  if (reload_completed)
    {

      extract_insn (make_insn_raw (x));
      constrain_operands (1);
      return which_alternative >= 0;
    }

  noperands = asm_noperands (x);
  if (noperands < 0)
    return 0;
  if (noperands == 0)
    return 1;

  operands = XALLOCAVEC (rtx, noperands);
  constraints = XALLOCAVEC (const char *, noperands);

  decode_asm_operands (x, operands, NULL, constraints, NULL, NULL);

  for (i = 0; i < noperands; i++)
    {
      const char *c = constraints[i];
      if (c[0] == '%')
	c++;
      if (! asm_operand_ok (operands[i], c, constraints))
	return 0;
    }

  return 1;
}
