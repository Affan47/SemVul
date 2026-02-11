createBinExpr (oper, expr1, expr2)
     short oper;
     chain_list *expr1, *expr2;
{
  chain_list *expr, *exprp;

  if (oper < MIN_OPER || oper > MAX_OPER || oper == NOT)
    {
      printf ("\ncreateBinExpr: error - bad operator %d\n", oper);
      exit (-1);
    }

  if (ATOM (expr1) || (OPER (expr1) != oper) ||
      ((oper == NOR) || (oper == NAND) || (oper == NXOR)))
    {

      expr = createExpr (oper);
      addHExpr (expr, expr1);
    }
  else
    {
      expr = expr1;
    }

  if (ATOM (expr2) || (OPER (expr2) != oper) ||
      ((oper == NOR) || (oper == NAND) || (oper == NXOR)))
    {

      addHExpr (expr, expr2);
    }
  else
    {

      exprp = expr2;
      while (CDR (exprp) != NULL)
	{
	  exprp = CDR (exprp);
	}
      exprp->NEXT = expr->NEXT;
      expr->NEXT = expr2->NEXT;
      expr2->NEXT = NULL;
      freeExpr (expr2);
    }
  return (expr);
}
