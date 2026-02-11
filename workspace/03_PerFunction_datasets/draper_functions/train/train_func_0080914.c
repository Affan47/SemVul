registerAtom(const Expr& e, const Theorem& thm)
{
  DebugAssert(!e.isEq() || e[0] != e[1], "expected non-reflexive");
  DebugAssert(!e.isRegisteredAtom(), "atom registered more than once");

  e.setRegisteredAtom();
  if(d_termTheorems.find(e) != d_termTheorems.end()){

  }

  d_termTheorems[e] = thm;
  DebugAssert(e.isAbsAtomicFormula(), "Expected atomic formula");
  ScopeWatcher sw(&d_inRegisterAtom);
  Theorem thm2 = simplify(e);
  if (thm2.getRHS().isTrue()) {
    setFindLiteral(d_commonRules->iffTrueElim(thm2));
  }
  else if (thm2.getRHS().isFalse()) {
    setFindLiteral(d_commonRules->iffFalseElim(thm2));
  }
  else {


    theoryOf(thm2.getRHS())->registerAtom(thm2.getRHS());
    setupSubFormulas(thm2.getRHS(), e, thm);
  }
  processFactQueue(LOW);
}
