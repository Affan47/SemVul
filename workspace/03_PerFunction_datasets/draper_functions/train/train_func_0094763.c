elimPower(const Expr& expr)
{
  if (CHECK_PROOFS) {
    CHECK_SOUND(expr.isEq() && isPow(expr[0]) &&
                isPow(expr[1]) &&
                isIntegerConst(expr[0][0]) &&
                expr[0][0].getRational() > 0 &&
                expr[0][0] == expr[1][0],
                "elimPower invariant violated"+expr.toString());
  }
  Proof pf;
  if (withProof()) {
    pf = newPf("elimPower", expr);
  }
  Rational r = expr[0][0].getRational();
  Expr res = expr[0][1].eqExpr(expr[1][1]);
  if (r % 2 == 0) {
    res = res.orExpr(expr[0][1].eqExpr(-expr[1][1]));
  }
  return newRWTheorem(expr, res, Assumptions::emptyAssump(), pf);
}
