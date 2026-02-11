realmedian(const GtBentsedgresources *bsr,
                                unsigned long subbucketleft,
                                unsigned long width,
                                unsigned long depth)
{
  GtMedianinfo *medianptr;
  unsigned long idx;

  for (idx = 0; idx < width; idx++)
  {
    bsr->medianinfospace[idx].suftaboffset = idx;
    PTR2INT(bsr->medianinfospace[idx].etbe,subbucketleft,idx);
  }
  medianptr = quickmedian(bsr->fwd,bsr->complement,bsr->medianinfospace,width);


  gt_assert(medianptr != NULL);
  return medianptr->suftaboffset;
}
