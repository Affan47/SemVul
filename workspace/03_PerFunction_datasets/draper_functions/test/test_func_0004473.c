median3(int *p)
{
  if (p[0] > p[1])
    return MAX(p[1],MIN(p[0],p[2]));
  else
    return MIN(p[1],MAX(p[0],p[2]));
}
