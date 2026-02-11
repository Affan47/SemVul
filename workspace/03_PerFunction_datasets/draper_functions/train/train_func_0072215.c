gt_createBWTSeqFromSfxI(const struct bwtParam *params, sfxInterface *sfxi,
                     GtError *err)
{
  BWTSeq *bwtSeq;
  SpecialsRankLookup *sprTable = NULL;
  const enum rangeSortMode *rangeSort;
  gt_assert(sfxi && params && err);
  buildSpRTable(params, gt_SfxIGetLength(sfxi), gt_SfxIGetEncSeq(sfxi),
                gt_SfxIGetReadmode(sfxi), &sprTable, &rangeSort);
  bwtSeq = gt_createBWTSeqFromSASS(params, gt_SfxI2SASS(sfxi), sprTable,
                                   rangeSort,
                                   err);
  if (sprTable)
    gt_deleteSpecialsRankLookup(sprTable);
  return bwtSeq;
}
