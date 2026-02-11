confIterIfThen(const Theorem& iter_th,
                                            bool left,
                                            const Theorem& ite_th,
                                            const Theorem& if_th,
                                            const Theorem& then_th)
{
  const Expr& iter_e(iter_th.getExpr());

  bool v0 = ite_th.proves(iter_e[0]);
  bool v1 = if_th.proves(iter_e[1]);
  bool v2 = then_th.proves(iter_e[left ? 2 : 3]);

  if (CHECK_PROOFS) {
    CHECK_SOUND(iter_e.getKind() == ITE_R &&
                (v0 || ite_th.refutes(iter_e[0])) &&
                (v1 || if_th.refutes(iter_e[1])) &&
                (v2 || then_th.refutes(iter_e[left ? 2 : 3])) &&
                v1 == left && v0 != v2,
                "SearchEngineTheoremProducer::confIterThenElse");
  }

  Assumptions a;
  Proof pf;
  if (withAssumptions()) {
    a.add(iter_th);
    a.add(ite_th);
    a.add(if_th);
    a.add(then_th);
  }

  if (withProof()) {
    vector<Proof> pfs;
    vector<Expr> exprs;
    exprs.push_back(iter_th.getExpr());
    exprs.push_back(ite_th.getExpr());
    exprs.push_back(if_th.getExpr());
    exprs.push_back(then_th.getExpr());
    pfs.push_back(iter_th.getProof());
    pfs.push_back(ite_th.getProof());
    pfs.push_back(if_th.getExpr());
    pfs.push_back(then_th.getExpr());
    pf = newPf("conf_iter_then_else", exprs, pfs);
  }

  return newTheorem(d_em->falseExpr(), a, pf);
}
