get_mem_expr_from_op (op, paddressp)
     rtx op;
     int *paddressp;
{
  tree expr;
  int inner_addressp;

  *paddressp = 0;

  if (op == NULL)
    return 0;

  if (GET_CODE (op) == REG && ORIGINAL_REGNO (op) >= FIRST_PSEUDO_REGISTER)
    return REGNO_DECL (ORIGINAL_REGNO (op));
  else if (GET_CODE (op) != MEM)
    return 0;

  if (MEM_EXPR (op) != 0)
    return MEM_EXPR (op);


  *paddressp = 1;
  op = XEXP (op, 0);


  if ((expr = get_mem_expr_from_op (op, &inner_addressp)) && ! inner_addressp)
    return expr;
  else if (GET_CODE (op) == PLUS
	   && (expr = get_mem_expr_from_op (XEXP (op, 1), &inner_addressp)))
    return expr;

  while (GET_RTX_CLASS (GET_CODE (op)) == '1'
	 || GET_RTX_CLASS (GET_CODE (op)) == '2')
    op = XEXP (op, 0);

  expr = get_mem_expr_from_op (op, &inner_addressp);
  return inner_addressp ? 0 : expr;
}
