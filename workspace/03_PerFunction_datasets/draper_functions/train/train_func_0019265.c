solve(const Theorem& t)
{
  DebugAssert(t.isRewrite() && t.getLHS().isTerm(), "");
  Expr e = t.getExpr();

  if (isLeaf(e[0]) && !isLeafIn(e[0], e[1])) {

    return t;
  }
  else if (isLeaf(e[1]) && !isLeafIn(e[1], e[0])) {
    return symmetryRule(t);
  }
  else if (e[0].getOpKind() == EXTRACT && isLeaf(e[0][0])) {
    bool solvedForm;
    Theorem thm;
    if (d_rules->solveExtractOverlapApplies(e))
    {
      thm = iffMP(t, d_rules->solveExtractOverlap(e));
      solvedForm = true;
    }
    else
      thm = d_rules->processExtract(t, solvedForm);

    thm = getCommonRules()->skolemize(thm);

    if (solvedForm) return thm;
    else {
      enqueueFact(getCommonRules()->andElim(thm, 1));
      return getCommonRules()->andElim(thm, 0);
    }
  }
  else if (e[1].getOpKind() == EXTRACT && isLeaf(e[1][0])) {
    bool solvedForm;
    Theorem thm = getCommonRules()->skolemize(d_rules->processExtract(symmetryRule(t), solvedForm));
    if (solvedForm) return thm;
    else {
      enqueueFact(getCommonRules()->andElim(thm, 1));
      return getCommonRules()->andElim(thm, 0);
    }
  }

  IF_DEBUG(
    Theorem t2 = iffMP(t, d_rules->canonBVEQ(e));
    if (e[0] < e[1]) {
      DebugAssert(e[1].getOpKind() == BVCONST,
                  "Should be only case when lhs < rhs");
      t2 = symmetryRule(t2);
    }
    DebugAssert(t2.getExpr() == e, "Expected no change");
  )

  if (e[0].getOpKind() == BVCONST) {
    DebugAssert(e[1].getOpKind() != BVCONST, "should not have const = const");
    return symmetryRule(t);
  }
  return t;
}
