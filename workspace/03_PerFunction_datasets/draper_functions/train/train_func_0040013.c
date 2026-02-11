PMExprInt (expr, pattern, bind)
     chain_list *expr, *pattern;
     ptype_list **bind;
{
  if (ATOM (pattern))
    {
      ptype_list *find = getptype (*bind, (long)VALUE_ATOM (pattern));


      if (find)
	{
	  if (!equalExpr (expr, (chain_list *) find->DATA))
	    return (0);
	}
      else
	*bind = addptype (*bind, (long)VALUE_ATOM (pattern), (void *)expr);

      return (1);
    }
  else

    {
      if (ATOM (expr))
	return (0);
      else

	{
	  if (OPER (expr) != OPER (pattern))
	    return (0);

	  if (lengthExpr (expr) != lengthExpr (pattern))
	    return (0);

	  while ((pattern = CDR (pattern)))
	    {
	      expr = CDR (expr);
	      if (PMExprInt (CAR (expr), CAR (pattern), bind) == 0)
		return (0);
	    }
	  return (1);
	}
    }
}
