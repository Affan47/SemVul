getImplication()
{

  Lit l;
  Theorem imp = d_core->getImpliedLiteral();
  while (!imp.isNull()) {
    l = d_cnfManager->getCNFLit(imp.getExpr());
    DebugAssert(!l.isNull() || imp.getExpr().unnegate().isUserRegisteredAtom(),
                "implied literals should be registered by cnf or by user");
    if (!l.isNull() && getValue(l) != Var::TRUE_VAL) {
      d_theorems.insert(imp.getExpr(), imp);
      break;
    }
    l.reset();
    imp = d_core->getImpliedLiteral();
  }
  return l;
}
