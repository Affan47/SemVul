transClosure(const Op& op) {
  const string& name = op.getExpr().getName();
  return d_em->newSymbolExpr(name, TRANS_CLOSURE).mkOp();
}
