rewriteTestCons(const Expr& e) {
  if (CHECK_PROOFS) {
    CHECK_SOUND(isTester(e), "Tester expected");
    CHECK_SOUND(isConstructor(e[0]), "Expected Test(Cons)");
  }
  Proof pf;
  Expr t;
  Expr cons = d_theoryDatatype->getConsForTester(e.getOpExpr());
  if (cons == getConstructor(e[0])) {
    t = d_theoryDatatype->trueExpr();
  }
  else {
    t = d_theoryDatatype->falseExpr();
  }
  if (withProof()) pf = newPf("rewriteTestCons", e, t);
  return newRWTheorem(e, t, Assumptions::emptyAssump(), pf);
}
