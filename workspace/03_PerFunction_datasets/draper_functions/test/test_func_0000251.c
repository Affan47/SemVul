gt_radixsort_space_ulong(GtRadixsortinfo *radixsortinfo)
{
  gt_assert(!radixsortinfo->pairs);
  return radixsortinfo->sortspace.ulongptr;
}
