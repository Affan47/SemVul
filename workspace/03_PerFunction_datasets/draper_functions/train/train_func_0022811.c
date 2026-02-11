gt_ranges_borders_are_in_region(GtArray *ranges, const GtRange *region)
{
  gt_assert(ranges && region);


  if (((GtRange*) gt_array_get_first(ranges))->start < region->start)
    return false;


  if (((GtRange*) gt_array_get_last(ranges))->end > region->end)
    return false;

  return true;
}
