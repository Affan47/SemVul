gt_differencecover_eval_lcp(const GtLcptrace *lcptrace,
                                                 const GtDifferencecover *dcov)
{
  if (lcptrace->idx1 < dcov->effectivesamplesize &&
      lcptrace->idx2 < dcov->effectivesamplesize)
  {
    gt_assert(dcov->rmq != NULL);
    return (unsigned long)
            gt_rmq_find_min_value(dcov->rmq,
                                  MIN(lcptrace->idx1,lcptrace->idx2)+1,
                                  MAX(lcptrace->idx1,lcptrace->idx2))
             + lcptrace->offset;
  }
  return (unsigned long) lcptrace->offset;
}
