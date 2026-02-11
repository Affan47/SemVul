relToClosure(const Theorem& rel)
{
  const Expr& relExpr = rel.getExpr();

  if(CHECK_PROOFS)
    CHECK_SOUND(relExpr.isApply() && relExpr.arity() == 2,
		CLASS_NAME
		"theorem is not a relation or has wrong arity:\n"
		+ rel.getExpr().toString());

  Proof pf;
  if(withProof()) {
    pf = newPf("rel_closure", rel.getProof());
  }

  const string& name = relExpr.getOp().getExpr().getName();
  Expr tc = d_theoryUF->transClosureExpr(name, relExpr[0], relExpr[1]);

  return newTheorem(tc, rel.getAssumptionsRef(), pf);
}
