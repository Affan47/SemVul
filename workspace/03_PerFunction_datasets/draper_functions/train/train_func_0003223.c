deriveClosure(const Theorem3& thm) {
  vector<Expr> assump;
  set<UserAssertion> assumpSet;


  Theorem3 res = thm;
  vector<Theorem> tccs;
  while(true) {
    {
      const Assumptions& a(res.getAssumptionsRef());
      if (a.empty()) break;
      assump.clear();
      assumpSet.clear();
      Assumptions::iterator i=a.begin(), iend=a.end();
      if(i!=iend) i->clearAllFlags();

      for(; i!=iend; ++i)
        getAssumptionsRec(*i, assumpSet, false);


      if(getFlags()["tcc"].getBool()) {
        tccs.clear();
        for(set<UserAssertion>::iterator i=assumpSet.begin(),
              iend=assumpSet.end(); i!=iend; ++i) {
          assump.push_back(i->thm().getExpr());
          tccs.push_back(i->tcc());
        }
      }
    }

    res = d_se->getCommonRules()->implIntro3(res, assump, tccs);
  }
  return res;
}
