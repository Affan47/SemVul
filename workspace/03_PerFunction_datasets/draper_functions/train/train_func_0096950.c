gt_array_iterate(GtArray *a, GtArrayProcessor array_processor, void *info,
                  GtError *err)
{
  unsigned long idx;
  int rval;
  gt_error_check(err);
  gt_assert(a && array_processor);
  for (idx = 0; idx < gt_array_size(a); idx++) {
    if ((rval = array_processor(gt_array_get(a, idx), info, err)))
      return rval;
  }
  return 0;
}
