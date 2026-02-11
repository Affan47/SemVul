pullIndex(const Expr& e, const Expr& index)
{
  DebugAssert(isWrite(e), "Expected write");

  if (e[1] == index) return reflexivityRule(e);


  if (!isWrite(e[0])) return Theorem();


  if (e[0][1] == index) {
    return d_rules->interchangeIndices(e);
  }


  Theorem thm = pullIndex(e[0], index);
  if (thm.isNull()) return thm;
  thm = substitutivityRule(e, 0, thm);
  thm = transitivityRule(thm, d_rules->interchangeIndices(thm.getRHS()));
  return thm;
}
