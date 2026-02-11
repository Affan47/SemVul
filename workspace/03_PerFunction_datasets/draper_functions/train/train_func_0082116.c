caseSplit(const Expr& a,
                                       const Theorem& a_proves_c,
                                       const Theorem& not_a_proves_c) {
  Expr c(a_proves_c.getExpr());

  if(CHECK_PROOFS) {
    CHECK_SOUND(c == not_a_proves_c.getExpr(),
                "caseSplit: conclusions differ:\n  positive case C = "
                + c.toString() + "\n  negative case C = "
                + not_a_proves_c.getExpr().toString());


  }

  const Assumptions& a1(a_proves_c.getAssumptionsRef());
  const Assumptions& a2(not_a_proves_c.getAssumptionsRef());
  Assumptions a3 = a1 - a;
  Assumptions a4 = a2 - !a;


  if (a1 == a3) return a_proves_c;
  if (a2 == a4) return not_a_proves_c;


  Proof pf;
  a3.add(a4);

  if(withProof()) {

    vector<Proof> pfs;
    pfs.push_back(newPf(a1[a].getProof(),
                        a, a_proves_c.getProof()));
    pfs.push_back(newPf(a2[!a].getProof(),
                        !a, not_a_proves_c.getProof()));
    pf = newPf("case_split", a, c, pfs);
  }
  return newTheorem(c, a3, pf);
}
