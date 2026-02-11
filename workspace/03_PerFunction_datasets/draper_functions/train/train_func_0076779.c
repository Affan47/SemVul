newBVMultPadExpr(int bvLength,
                                       const Expr& t1, const Expr& t2)
{
  return newBVMultExpr(bvLength, pad(bvLength, t1), pad(bvLength, t2));
}
