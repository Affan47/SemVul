isCandidate(IntegerVector const &v, const TermOrder &source, const TermOrder &target)
{
  return !source(v,v,1,0) && target(v,v,1,0);
}
