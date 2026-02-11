lessThanVar(const Expr& isolatedMonomial, const Expr& var2)
{
  DebugAssert(!isRational(var2) && !isRational(isolatedMonomial),
              "TheoryArith3::findMaxVar: isolatedMonomial cannot be rational" +
              isolatedMonomial.toString());
  Expr c, var0, var1;
  separateMonomial(isolatedMonomial, c, var0);
  separateMonomial(var2, c, var1);
  return var0 < var1;
}
