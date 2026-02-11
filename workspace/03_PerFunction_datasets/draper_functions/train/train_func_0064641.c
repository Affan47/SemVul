gt_bool_matrix_get_first_column(const GtBoolMatrix *bm,
                                              unsigned long firstdim)
{
  GtDynBittab *bt;
  gt_assert(bm);
  if (firstdim < gt_array_size(bm->dyn_bittabs)) {
    if ((bt = *(GtDynBittab**) gt_array_get(bm->dyn_bittabs, firstdim)))
      return gt_dyn_bittab_get_first_bitnum(bt);
  }
  return GT_UNDEF_ULONG;
}
