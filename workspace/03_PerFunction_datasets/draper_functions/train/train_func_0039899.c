gt_cntlist_parse_bit(FILE *infp, bool alloc_cntlist,
    GtBitsequence **cntlist, unsigned long *nofreads, GtError *err)
{
  int had_err = gt_cntlist_parse_bin_or_bit_header(infp, nofreads, err);
  if (had_err == 0)
  {
    size_t n;
    gt_assert(cntlist != NULL);
    if (alloc_cntlist)
    {
      GT_INITBITTAB(*cntlist, *nofreads);
      n = fread(*cntlist, sizeof (GtBitsequence),
          GT_NUMOFINTSFORBITS(*nofreads), infp);
      if (n != GT_NUMOFINTSFORBITS(*nofreads))
      {
        gt_error_set(err, "contained reads file: unrecognized format");
        had_err = -1;
      }
    }
    else
    {

      size_t i;
      for (i = 0; i < GT_NUMOFINTSFORBITS(*nofreads); i++)
      {
        GtBitsequence value;
        n = fread(&value, sizeof (GtBitsequence), (size_t)1, infp);
        if (n != (size_t)1)
        {
          gt_error_set(err, "contained reads file: unrecognized format");
          had_err = -1;
          break;
        }
        *cntlist[i] |= value;
      }
    }
  }
  return had_err;
}
