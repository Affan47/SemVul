CMSegmentCountStatetype(CM_t *cm, int r, int z, char type)
{
  int count = 0;
  int v;
  for (v = r; v <= z; v++)
    if (cm->sttype[v] == type) count++;
  return count;
}
