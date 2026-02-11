devXorExpr (expr)
     chain_list *expr;
{
  if (ATOM (expr))
    return copyExpr (expr);
  else
    {
      if (OPER (expr) != XOR)
	return mapCarExpr (devXorExpr, OPER (expr), expr);
      else if (lengthExpr (expr) == 2)
	{
	  chain_list *dev, *ret;

	  dev = devXor2Expr (expr);
	  ret = devXorExpr (dev);
	  freeExpr (dev);
	  return (ret);
	}
      else
	{

	  chain_list *xor, *dev, *inter;

	  xor = createExpr (XOR);
	  addHExpr (xor, copyExpr (CADR (expr)));


	  inter = createExpr (XOR);
	  expr = CDR (expr);
	  while ((expr = CDR (expr)))
	    addHExpr (inter, copyExpr (CAR (expr)));

	  dev = devXorExpr (inter);
	  freeExpr (inter);

	  addQExpr (xor, dev);
	  dev = devXor2Expr (xor);
	  freeExpr (xor);
	  return (dev);
	}
    }
}
