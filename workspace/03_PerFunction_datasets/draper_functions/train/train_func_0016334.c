remegalExpr (expr)
     chain_list *expr;
{
  if (ATOM (expr))
    return (copyExpr (expr));
  else
    {
      chain_list *ret;

      if ((OPER (expr) == NOT) && !ATOM (CADR (expr)) && (OPER (CADR (expr)) == XOR))
	{
	  chain_list *filsExpr;
	  chain_list *filsCst;

	  filsExpr = CADR (expr);
	  filsCst = CADR (CDR (filsExpr));

	  if (ATOM (filsCst) && !strcmp (VALUE_ATOM (filsCst), "'1'"))
	    {
	      return (copyExpr (CADR (filsExpr)));
	    }
	  if (ATOM (filsCst) && !strcmp (VALUE_ATOM (filsCst), "'0'"))
	    {
	      return (notExpr (copyExpr (CADR (filsExpr))));
	    }
	}

      ret = createExpr (OPER (expr));

      while ((expr = CDR (expr)))
	{
	  addQExpr (ret, remegalExpr (CAR (expr)));
	}
      return (ret);
    }
}
