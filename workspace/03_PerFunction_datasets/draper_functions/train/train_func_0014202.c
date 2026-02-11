output_asm_operand_names (rtx *operands, int *oporder, int nops)
{
  int wrote = 0;
  int i;

  for (i = 0; i < nops; i++)
    {
      int addressp;
      rtx op = operands[oporder[i]];
      tree expr = get_mem_expr_from_op (op, &addressp);

      fprintf (asm_out_file, "%c%s",
	       wrote ? ',' : '\t', wrote ? "" : ASM_COMMENT_START);
      wrote = 1;
      if (expr)
	{
	  fprintf (asm_out_file, "%s",
		   addressp ? "*" : "");
	  print_mem_expr (asm_out_file, expr);
	  wrote = 1;
	}
      else if (REG_P (op) && ORIGINAL_REGNO (op)
	       && ORIGINAL_REGNO (op) != REGNO (op))
	fprintf (asm_out_file, " tmp%i", ORIGINAL_REGNO (op));
    }
}
