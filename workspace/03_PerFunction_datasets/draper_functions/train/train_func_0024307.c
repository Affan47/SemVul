gt_range_within(const GtRange *range, unsigned long point)
{
  gt_assert(range->start <= range->end);

  if (range->start <= point && range->end >= point)
    return true;
  return false;
}
