implMP(const Theorem& e1,
                                      const Theorem& e1_impl_e2) {
  const Expr& impl = e1_impl_e2.getExpr();
  if(CHECK_PROOFS) {
    CHECK_SOUND(impl.isImpl() && impl.arity()==2,
		"implMP: not IMPLIES: "+impl.toString());
    CHECK_SOUND(e1.getExpr() == impl[0],
		"implMP: theorems don't match:\n  e1 = " + e1.toString()
		+ ", e1_impl_e2 = " + impl.toString());
  }
  const Expr& e2 = impl[1];


  Proof pf;
  Assumptions a(e1, e1_impl_e2);
  if(withProof()) {
    vector<Proof> pfs;
    pfs.push_back(e1.getProof());
    pfs.push_back(e1_impl_e2.getProof());
    pf = newPf("impl_mp", e1.getExpr(), e2, pfs);
  }
  return newTheorem(e2, a, pf);
}
