tmmatch(TransformStruct **a, TransformStruct **b)
{
  if ((*a)->h && ((*a)->h == (*b)->h)) return 1;
  if ((*a)->tm && ((*a)->tm == (*b)->tm)) return 1;
  return TmCompare((*a)->tm, (*b)->tm, (float)0.0);
}
