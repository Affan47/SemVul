inversesuffixarray2specialranknext(
                         const GtCompactUlongStore *rightposinverse,
                         GtCompactUlongStore *ranknext,
                         const GtEncseq *encseq,
                         GtReadmode readmode,
                         unsigned long partwidth,
                         unsigned long totallength)
{
  if (gt_encseq_has_specialranges(encseq))
  {
    GtSpecialrangeiterator *sri;
    GtRange range;
    unsigned long idx, *rightofpartwidth = NULL,
                  specialranklistindex, nextrightofpartwidth = 0;

    rightofpartwidth = fillrightofpartwidth(rightposinverse,
                                            encseq,
                                            readmode,
                                            partwidth,
                                            totallength);
    specialranklistindex = partwidth;
    sri = gt_specialrangeiterator_new(encseq,
                                      GT_ISDIRREVERSE(readmode) ? false : true);
    nextrightofpartwidth = 0;
    while (gt_specialrangeiterator_next(sri,&range))
    {
      if (GT_ISDIRREVERSE(readmode))
      {
        gt_range_reverse(totallength,&range);
      }
      gt_assert(range.end <= totallength);
      for (idx = range.start; idx < range.end-1; idx++)
      {
        gt_assert(specialranklistindex < totallength);
        gt_compact_ulong_store_update(ranknext,specialranklistindex,
                                      specialranklistindex + 1);
        specialranklistindex++;
      }
      gt_assert(specialranklistindex < totallength);
      if (range.end < partwidth)
      {
        gt_compact_ulong_store_update(ranknext,specialranklistindex,
                                      gt_compact_ulong_store_get(
                                             rightposinverse,range.end));
      } else
      {
        gt_compact_ulong_store_update(ranknext,specialranklistindex,
                                      rightofpartwidth[nextrightofpartwidth]);
        nextrightofpartwidth++;
      }
      specialranklistindex++;
    }
    gt_free(rightofpartwidth);
    gt_assert(specialranklistindex == totallength);
    gt_specialrangeiterator_delete(sri);
  }
}
