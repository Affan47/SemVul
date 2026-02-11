isFacet(const IntegerVectorList &g, IntegerVectorList::const_iterator i)
{
  TimerScope ts(&lpTimer);
  LpInit();

  return default_->isFacet(g,i);
}
