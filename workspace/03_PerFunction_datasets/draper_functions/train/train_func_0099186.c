gt_array_get_last(const GtArray *a)
{
  gt_assert(a->next_free);
  return gt_array_get(a, a->next_free-1);
}
