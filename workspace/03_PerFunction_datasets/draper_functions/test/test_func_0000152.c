gt_sampling_get_next_elementnum(GtSampling *sampling)
{
  gt_assert(sampling->arraysize == sampling->numofsamples);
  gt_assert(sampling->current_sample_num < sampling->numofsamples);
  if (sampling->current_sample_num + 1 == sampling->numofsamples)
    return 0;
  gt_assert((sampling->current_sample_num + 1) < sampling->arraysize);
  switch (sampling->method) {
    case GT_SAMPLING_REGULAR:
      return sampling->current_sample_elementnum + sampling->sampling_rate;
    case GT_SAMPLING_PAGES:
      return sampling->page_sampling[sampling->current_sample_num + 1];
    default:
      return GT_UNDEF_ULONG;
  }
}
