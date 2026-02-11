pushNegationRec(const Theorem& thm, bool neg) {
  DebugAssert(thm.isRewrite(), "pushNegationRec(Theorem): bad theorem: "
	      + thm.toString());
  Expr e(thm.getRHS());
  if(neg) {
    DebugAssert(e.isNot(),
		"pushNegationRec(Theorem, neg = true): bad Theorem: "
		+ thm.toString());
    e = e[0];
  }
  return d_commonRules->transitivityRule(thm, pushNegationRec(e, neg));
}
