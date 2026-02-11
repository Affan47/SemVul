expandtwocharcode(GtCodetype twocharcode,
                                  const GtBucketspec2 *bucketspec2)
{
  gt_assert(twocharcode < (GtCodetype) bucketspec2->numofcharssquared);
  return twocharcode * bucketspec2->expandfactor + bucketspec2->expandfillsum;
}
