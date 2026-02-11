gt_randomcodes_countocc_new(GtFirstcodesspacelog *fcsl,
                                       GtRandomcodestab *rct,
                                       unsigned long numofsequences)
{
  rct->countocc_small = gt_calloc((size_t) (numofsequences+1),
                                  sizeof (*rct->countocc_small));
  GT_FCI_ADDWORKSPACE(fcsl,"countocc_small",
                      sizeof (*rct->countocc_small) *
                      (numofsequences+1));
  rct->countocc_exceptions = ul_u32_gt_hashmap_new();
  gt_assert(rct->countocc_exceptions != NULL);
  rct->outfilenameleftborder = NULL;
  rct->leftborder_samples = NULL;
#ifdef _LP64
  rct->modvaluebits = 32U;
  if (rct->modvaluebits == 32U)
  {
    rct->modvaluemask = UINT32_MAX;
  } else
  {
    rct->modvaluemask = (uint32_t) ((1UL << rct->modvaluebits) - 1);
  }
  GT_INITARRAY(&rct->bitchangepoints,GtUlong);
#endif
  rct->differentcodes = numofsequences;
}
