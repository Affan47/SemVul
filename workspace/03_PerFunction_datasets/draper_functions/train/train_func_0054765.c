rewriteIteElse(const Expr& e, const Theorem& elseThm) {
  Proof pf;
  if(CHECK_PROOFS) {
    CHECK_SOUND(withAssumptions(), "Cannot check proof without assumptions");
    CHECK_SOUND(e.isITE() && elseThm.isRewrite() && e[2] == elseThm.getLHS(),
		"rewriteIteElse precondition violated \n else expression: "
		+ elseThm.getExpr().toString() + "\n e = " + e.toString());
  }
  Assumptions a = elseThm.getAssumptionsRef() - !e[0];
  if(withProof()) {
    Type t = e.getType();
    DebugAssert(!t.isNull(), "rewriteIteElse: e has no type: "
		+ e.toString());
    bool useIff = t.isBool();
    if(useIff)
      pf = newPf("rewrite_ite_else_iff", e, elseThm.getProof());
    else {
      pf = newPf("rewrite_ite_else", e, elseThm.getProof());
    }
  }
  return newRWTheorem(e, e[0].iteExpr(e[1], elseThm.getRHS()), a, pf);
}
