gth_backtrace_path_get(const GthBacktracePath *bp)
{
  gt_assert(bp);
  return (Editoperation*) gt_array_get_space(bp->editoperations)
         + bp->cutoffs.end.eopcutoff;
}
