_gcry_enum_hw_features (int idx, unsigned int *r_feature)
{
  if (idx < 0 || idx >= DIM (hwflist))
    return NULL;
  if (r_feature)
    *r_feature = hwflist[idx].flag;
  return hwflist[idx].desc;
}
