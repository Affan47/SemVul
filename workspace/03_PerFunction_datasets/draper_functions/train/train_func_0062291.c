freeExpr (expr)
     chain_list *expr;
{
  chain_list *pt;

 if (expr)
  {
      if (ATOM (expr))
	  freechain (expr);
      else
      {
	  pt = expr;
	  delchain (CAR (expr), CAR (expr));
	  while ((expr = CDR (expr)))
	      freeExpr (CAR (expr));
	  freechain (pt);
      }
  }
}
