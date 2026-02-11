intVarEqnConst(const Expr& eqn,
				     const Theorem& isIntx) {
  const Expr& left(eqn[0]);
  const Expr& right(eqn[1]);
  const Expr& isIntxexpr(isIntx.getExpr());

  if(CHECK_PROOFS) {
    CHECK_SOUND((isMult(right) && right[0].isRational())
                || (right.arity() == 2 && isPlus(right)
                    && right[0].isRational()
                    && ((!isMult(right[1]) || right[1][0].isRational()))),
                "ArithTheoremProducer::intVarEqnConst: "
		"rhs has a wrong format: " + right.toString());
    CHECK_SOUND(left.isRational() && 0 == left.getRational(),
                "ArithTheoremProducer:intVarEqnConst:left is not a zero: " +
                left.toString());
  }

  Expr x(right);
  Rational a(1), c(0);
  if(isMult(right)) {
    Expr aExpr;
    d_theoryArith->separateMonomial(right, aExpr, x);
    a = aExpr.getRational();
  } else {
    c = right[0].getRational();
    Expr aExpr;
    d_theoryArith->separateMonomial(right[1], aExpr, x);
    a = aExpr.getRational();
  }
  if(CHECK_PROOFS) {
    CHECK_SOUND(isIntPred(isIntxexpr) && isIntxexpr[0] == x,
                "ArithTheoremProducer:intVarEqnConst: "
		"bad integrality constraint:\n right = " +
                right.toString()+"\n isIntx = "+isIntxexpr.toString());
    CHECK_SOUND(a!=0, "ArithTheoremProducer:intVarEqnConst: eqn = "
		+eqn.toString());
  }
  const Assumptions& assump(isIntx.getAssumptionsRef());
  Proof pf;
  if(withProof())
    pf = newPf("int_const_eq", eqn, isIntx.getProof());


  Rational r(-c/a);

  if(r.isInteger())
    return newRWTheorem(eqn, x.eqExpr(rat(r)), assump, pf);
  else
    return newRWTheorem(eqn, d_em->falseExpr(), assump, pf);
}
