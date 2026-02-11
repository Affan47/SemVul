canonUMinusToDivide(const Expr& e) {
  Proof pf;
  if(withProof()) pf = newPf("canon_uminus", e);
  return newRWTheorem((-e), (e / rat(-1)), Assumptions::emptyAssump(), pf);
}
