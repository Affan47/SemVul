gth_backtrace_path_remove_zero_base_exons(GthBacktracePath *bp,
                                               GthStat *stat)
{
  gt_assert(bp);
  gt_remove_zero_base_exons(gth_backtrace_path_get(bp),
                         gth_backtrace_path_length(bp), stat);
}
