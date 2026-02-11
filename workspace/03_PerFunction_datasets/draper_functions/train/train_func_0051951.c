subtree(Tree X, int i, const Path& p)
{
  int n = p.size();
  Node op(0);
  Tree x0, x1;
  if (i < n && isBoxPatternOp(X, op, x0, x1))
    return subtree((p[i]==0)?x0:x1, i+1, p);
  else
    return X;
}
