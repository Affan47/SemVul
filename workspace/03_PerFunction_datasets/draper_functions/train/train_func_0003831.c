gt_reads2twobit_encode(GtReads2Twobit *r2t, GtError *err)
{
  int had_err = 0;
  const unsigned long noflibraries = gt_array_size(r2t->collection);
  unsigned long libnum;
  GtReads2TwobitEncodeState state;

  gt_error_check(err);
  gt_assert(r2t != NULL);
  gt_assert(r2t->twobitencoding == NULL);
  gt_reads2twobit_init_encode(r2t, &state);
  for (libnum = 0; libnum < noflibraries && !had_err; libnum++)
  {
    GtReadsLibraryInfo *rli = gt_array_get(r2t->collection, libnum);
    if (!rli->paired)
    {
      had_err = gt_reads2twobit_encode_unpaired_library(&state, rli, err);
    }
    else
    {
      had_err = gt_reads2twobit_encode_paired_library(&state, rli, err);
    }
  }
  gt_reads2twobit_finalize_encode(r2t, &state);
  return had_err;
}
