gt_array_sort_stable(GtArray *a, GtCompare compar)
{
  gt_assert(a && compar);
  gt_msort(a->space, a->next_free, a->size_of_elem, compar);
}
