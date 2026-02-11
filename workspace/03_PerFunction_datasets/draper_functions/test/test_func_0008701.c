assumpRule(const Expr& e, int scope) {

  Proof pf;
  if(withProof()) pf = newLabel(e);
  return newAssumption(e, pf, scope);
}
