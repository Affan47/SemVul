operator[] (int n_child)
{
  const int for_err = n_child;
  SExprIter i;
  for (i = child.begin(); i != child.end() && n_child > 0; --n_child, ++i)
    { }
  if (i == child.end())
    THROWEXPR ("In SExpr (" << *this << "):\nI was expecting this to be a list with at least " << (for_err+1) << " child"<<(for_err==0?"":"ren") << " but I can't find the child at index #" << for_err);
  return *i;
}
