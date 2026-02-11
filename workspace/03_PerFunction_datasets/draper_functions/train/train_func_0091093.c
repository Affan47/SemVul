rewriteIteToNot(const Expr& e)
{
  if (CHECK_PROOFS)
    CHECK_SOUND(e.isITE() && e[1].isFalse() && e[2].isTrue(),
		"rewriteIteToNot: " + e.toString());
  Proof pf;
  if (withProof()) pf = newPf("rewrite_ite_to_not", e);
  return newRWTheorem(e, e[0].negate(), Assumptions::emptyAssump(), pf);
}
