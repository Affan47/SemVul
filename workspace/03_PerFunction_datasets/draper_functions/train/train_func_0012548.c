leavesAreSimp(const Expr& e)
{
  if (isLeaf(e)) {
    return !e.hasFind() || e.getFind().getRHS() == e;
  }
  for (int k = 0; k < e.arity(); ++k) {
    if (!leavesAreSimp(e[k])) return false;
  }
  return true;
}
