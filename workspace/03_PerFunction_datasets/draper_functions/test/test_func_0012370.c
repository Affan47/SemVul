numberOfPivots()const
{
  int ret=0;
  int pivotI=-1;
  int pivotJ=-1;
  while(nextPivot(pivotI,pivotJ))ret++;
  return ret;
}
