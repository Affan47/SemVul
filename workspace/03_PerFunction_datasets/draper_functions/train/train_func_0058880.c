deriveThmRec(bool checkAssump) const {
  DebugAssert(!isNull(), "Variable::deriveTheorem(): called on Null");
  DebugAssert(getValue() != 0, "Variable::deriveTheorem(): value is not set: "
	      + toString());
  if(!getTheorem().isNull()) return getTheorem();
  if(checkAssump && !getAssumpThm().isNull()) return getAssumpThm();

  Clause c(getAntecedent());
  int idx(getAntecedentIdx());
  const vector<Literal>& lits = c.getLiterals();

  vector<Theorem> thms;
  int size(lits.size());

  for(int i=0; i<size; ++i)
    if(i!=idx) thms.push_back(lits[i].getVar().deriveThmRec(true));
  Theorem thm;
  if(idx!=-1)
    thm = d_val->d_vm->getRules()->unitProp(thms, c.getTheorem(), idx);
  else
    thm = d_val->d_vm->getRules()->conflictRule(thms, c.getTheorem());

  IF_DEBUG(Expr e(thm.getExpr());)
  DebugAssert(e == getExpr()
	      || (e.isNot() && e[0] == getExpr()),
	      "Variable::deriveTheorem: bad theorem derived: expr ="
	      + toString() + ", thm = " + thm.toString());

  d_val->setValue(thm, getScope());
  return thm;
}
