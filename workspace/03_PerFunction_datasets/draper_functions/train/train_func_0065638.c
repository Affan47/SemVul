getAssumptionsRec(set<Expr>& assumptions) const
{
  if (isRefl() || isFlagged()) return;
  setFlag();
  if(isAssump()) {
    assumptions.insert(getExpr());
  }
  else {
    const Assumptions& a = getAssumptionsRef();
    for(Assumptions::iterator i=a.begin(), iend=a.end(); i!=iend; ++i)
      (*i).getAssumptionsRec(assumptions);
  }
}
