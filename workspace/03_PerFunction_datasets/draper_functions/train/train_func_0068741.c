processResult(const Theorem& res, const Expr& e)
{

  DebugAssert(res.isNull() || res.getExpr().isFalse(),
	      "processResult: bad input"
	      + res.toString());
  if(res.isNull()) {


    d_lastValid = Theorem();

    d_lastCounterExample.erase(!e);
    if (e.isNot()) d_lastCounterExample.erase(e[0]);
  } else {

    Theorem res2 =
      d_rules->eliminateSkolemAxioms(res, d_commonRules->getSkolemAxioms());
    if(e.isNot())
      d_lastValid = d_rules->negIntro(e, res2);
    else
      d_lastValid = d_rules->proofByContradiction(e, res2);
    d_lastCounterExample.clear();
  }
}
