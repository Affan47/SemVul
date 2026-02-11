backwardderive(const GtBucketspec2 *bucketspec2,
                           GtSuffixsortspace *suffixsortspace,
                           unsigned long *targetoffset,
                           unsigned int source,
                           unsigned long idx)
{
  unsigned long startpos;
  GtUchar cc;

  for (; idx + 1 > targetoffset[source] + 1; idx--)
  {
    startpos = gt_suffixsortspace_getdirect(suffixsortspace,idx);
    if (startpos > 0)
    {
      cc = gt_encseq_get_encoded_char(bucketspec2->encseq,
                                      startpos-1,
                                      bucketspec2->readmode);
      if (ISNOTSPECIAL(cc) && !bucketspec2->superbuckettab[cc].sorted)
      {
        gt_suffixsortspace_setdirect(suffixsortspace,targetoffset[cc],
                                     startpos - 1);
        targetoffset[cc]--;
      }
    }
  }
}
