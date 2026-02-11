getAssumptionsAndCongRec(set<Expr>& assumptions,
                                       vector<Expr>& congruences) const
{
  if (isRefl() || isFlagged()) return;
  setFlag();
  if(isAssump()) {
    assumptions.insert(getExpr());
  }
  else {
    const Assumptions& a = getAssumptionsRef();
    if (isSubst() && a.size() == 1) {
      vector<Expr> hyp;
      const Theorem& thm = *(a.begin());
      thm.getAssumptionsAndCongRec(assumptions, congruences);
      if (thm.isRewrite() && thm.getLHS().isTerm()
          && thm.getLHS().isAtomic() && thm.getRHS().isAtomic() &&
          !thm.isRefl()) {
        hyp.push_back(!thm.getExpr());
      }
      else return;
      const Expr& e = getExpr();
      if (e.isAtomicFormula()) {
        if (e[0] < e[1]) {
          hyp.push_back(e[1].eqExpr(e[0]));
        }
        else {
          hyp.push_back(e);
        }
        congruences.push_back(Expr(OR, hyp));
      }
      else if (e[0].isAtomicFormula() && !e[0].isEq()) {
        hyp.push_back(!e[0]);
        hyp.push_back(e[1]);
        congruences.push_back(Expr(OR, hyp));
        hyp.pop_back();
        hyp.pop_back();
        hyp.push_back(e[0]);
        hyp.push_back(!e[1]);
        congruences.push_back(Expr(OR, hyp));
      }
    }
    else {
      Assumptions::iterator i=a.begin(), iend=a.end();
      for(; i!=iend; ++i)
        (*i).getAssumptionsAndCongRec(assumptions, congruences);
    }
  }
}
