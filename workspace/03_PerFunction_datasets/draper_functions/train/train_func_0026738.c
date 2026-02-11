pseudo_compare_func (const void *v1p, const void *v2p)
{
  int r1 = *(const int *) v1p, r2 = *(const int *) v2p;
  int diff;


  if ((diff = lra_reg_info[r2].freq - lra_reg_info[r1].freq) != 0)
    return diff;


  return r1 - r2;
}
