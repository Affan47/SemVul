ifLiftRule(const Expr& e, int itePos) {
  if(CHECK_PROOFS) {
    CHECK_SOUND(e.getType().isBool(),
		"CNF_TheoremProducer::ifLiftRule("
		"input must be a Predicate: e = " + e.toString()+")");
    CHECK_SOUND(itePos >= 0, "itePos negative"+int2string(itePos));
    CHECK_SOUND(e.arity() > itePos && e[itePos].isITE(),
		"CNF_TheoremProducer::ifLiftRule("
		"input does not have an ITE: e = " + e.toString()+")");
  }
  const Expr& ite = e[itePos];
  const Expr& cond = ite[0];
  const Expr& t1 = ite[1];
  const Expr& t2 = ite[2];

  if(CHECK_PROOFS) {
    CHECK_SOUND(cond.getType().isBool(),
		"CNF_TheoremProducer::ifLiftRule("
		"input does not have an ITE: e = " + e.toString()+")");
  }

  vector<Expr> k1 = e.getKids();
  Op op(e.getOp());

  k1[itePos] = t1;
  Expr pred1 =  Expr(op, k1);

  k1[itePos] = t2;
  Expr pred2 =  Expr(op, k1);

  Expr resultITE = cond.iteExpr(pred1, pred2);

  Proof pf;
  if (withProof())
    pf = newPf("if_lift_rule", e, resultITE, d_em->newRatExpr(itePos));
  return newRWTheorem(e, resultITE, Assumptions::emptyAssump(), pf);
}
