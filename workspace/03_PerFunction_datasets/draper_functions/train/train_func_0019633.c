getCounterExample(vector<Expr>& assertions, bool inOrder)
{
  if(d_dump) {
    d_translator->dump(d_em->newLeafExpr(COUNTEREXAMPLE), true);
  }
  if (!(*d_flags)["translate"].getBool())
    d_se->getCounterExample(assertions, inOrder);
}
