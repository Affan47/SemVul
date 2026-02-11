iffTrue(const Theorem& e)
{
  Proof pf;
  if(withProof()) {
    pf = newPf("iff_true", e.getExpr(), e.getProof());
  }
  return newRWTheorem(e.getExpr(), d_em->trueExpr(), Assumptions(e), pf);
}
