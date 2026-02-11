assertLit(Lit l)
{

  Expr e = d_cnfManager->concreteLit(l);

  IF_DEBUG(
  string indentStr(theoryCore()->getCM()->scopeLevel(), ' ');
  string val = " := ";

  std::stringstream ss;
  ss<<theoryCore()->getCM()->scopeLevel();
  std::string temp;
  ss>>temp;

  if (l.isPositive()) val += "1"; else val += "0";
  TRACE("assertLit", "", "", "");
  TRACE("assertLitScope", indentStr, "Scope level = ", temp);
  TRACE("assertLit", indentStr, l.getVar(), val+": "+e.toString());
  )


  bool isSATLemma = false;
  if (e.isNull()) {
    e = d_cnfManager->concreteLit(l, false);
    DebugAssert(!e.isNull(), "Expected known expr");
    isSATLemma = true;
    TRACE("quant-level", "found null expr ",e, "");
  }

  DebugAssert(!e.isNull(), "Expected known expr");
  DebugAssert(!e.isIntAssumption() || getValue(l) == SAT::Var::TRUE_VAL,
              "internal assumptions should be true");

  if (e.isIntAssumption()) return;
  if (getValue(l) == SAT::Var::UNKNOWN) {
    setValue(l.getVar(), l.isPositive() ? Var::TRUE_VAL : Var::FALSE_VAL);
  }
  else {
    DebugAssert(!e.isAbsLiteral(), "invariant violated");
    DebugAssert(getValue(l) == Var::TRUE_VAL, "invariant violated");
    return;
  }
  if (!e.isAbsLiteral()) return;
  e.setIntAssumption();

  Theorem thm = d_commonRules->assumpRule(e);
  if (isSATLemma) {
    CNF_Formula_Impl cnf;
    d_cnfManager->addAssumption(thm, cnf);
  }

  thm.setQuantLevel(theoryCore()->getQuantLevelForTerm(e.isNot() ? e[0] : e));
  d_intAssumptions.push_back(thm);
  d_core->addFact(thm);
}
