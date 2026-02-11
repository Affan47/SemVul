he_cmp_slow (const void *a, const void *b)
{
  return sv_cmp (HeSVKEY_force (*(HE **)b), HeSVKEY_force (*(HE **)a));
}
