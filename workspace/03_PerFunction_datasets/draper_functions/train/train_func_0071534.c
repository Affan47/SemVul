type(int t)
{
  if (t<0) return 0;
  if (t<_realCount) return _real[t];

  t -= ProfileCostArray::MaxRealIndex;
  if (t<0) return 0;
  if (t<_derivedCount) return _derived[t];

  return 0;
}
