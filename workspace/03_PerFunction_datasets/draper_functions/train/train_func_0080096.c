replaceITErec(const Expr& e, Var v, bool translateOnly)
{

  if (e.isAtomic()) return d_commonRules->reflexivityRule(e);


  Theorem thm;
  bool foundInCache = false;
  ExprHashMap<Theorem>::iterator iMap = d_iteMap.find(e);
  if (iMap != d_iteMap.end()) {
    thm = (*iMap).second;
    foundInCache = true;
  }

  if (e.getKind() == ITE) {

    DebugAssert(!e.getType().isBool(), "Expected non-Bool ITE");

    if (!foundInCache) thm = d_commonRules->varIntroSkolem(e);
    Theorem thm2 = d_commonRules->symmetryRule(thm);
    thm2 = d_commonRules->iffMP(thm2, d_rules->ifLiftRule(thm2.getExpr(), 1));
    d_translateQueueVars.push_back(v);
    d_translateQueueThms.push_back(thm2);
    d_translateQueueFlags.push_back(translateOnly);
  }
  else {

    vector<Theorem> thms;
    vector<unsigned> changed;
    unsigned index = 0;
    Expr::iterator i, iend;
    if (foundInCache) {
      for(i = e.begin(), iend = e.end(); i!=iend; ++i, ++index) {
        replaceITErec(*i, v, translateOnly);
      }
    }
    else {
      for(i = e.begin(), iend = e.end(); i!=iend; ++i, ++index) {
        thm = replaceITErec(*i, v, translateOnly);
        if (!thm.isRefl()) {
          thms.push_back(thm);
          changed.push_back(index);
        }
      }
      if(changed.size() > 0) {
        thm = d_commonRules->substitutivityRule(e, changed, thms);
      }
      else thm = d_commonRules->reflexivityRule(e);
    }
  }


  if (!foundInCache) d_iteMap[e] = thm;
  return thm;
}
