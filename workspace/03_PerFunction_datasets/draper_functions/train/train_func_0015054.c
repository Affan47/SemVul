superbucketsize(const GtBucketspec2 *bucketspec2,
                                     unsigned int bucketnum)
{
  if (bucketnum == 0)
  {
    return bucketspec2->superbuckettab[0].bucketend;
  }
  return bucketspec2->superbuckettab[bucketnum].bucketend -
         bucketspec2->superbuckettab[bucketnum-1].bucketend;
}
