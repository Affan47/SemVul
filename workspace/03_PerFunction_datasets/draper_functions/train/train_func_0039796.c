gt_readjoiner_assembly_count_spm(const char *readset, bool eqlen,
    unsigned int minmatchlength, unsigned int nspmfiles, GtStrgraph *strgraph,
    GtBitsequence *contained, GtLogger *default_logger, GtError *err)
{
  GtSpmprocSkipData skipdata;
  int had_err = 0;
  unsigned int i;
  GtStr *filename = gt_str_new();
  gt_logger_log(default_logger, GT_READJOINER_MSG_COUNTSPM);
  if (!eqlen)
  {
    skipdata.out.e.proc = gt_spmproc_strgraph_count;
    skipdata.to_skip = contained;
    skipdata.out.e.data = strgraph;
  }
  for (i = 0; i < nspmfiles; i++)
  {
    gt_str_append_cstr(filename, readset);
    gt_str_append_char(filename, '.');
    gt_str_append_uint(filename, i);
    gt_str_append_cstr(filename, GT_READJOINER_SUFFIX_SPMLIST);
    had_err = gt_spmlist_parse(gt_str_get(filename),
        (unsigned long)minmatchlength,
        eqlen ? gt_spmproc_strgraph_count : gt_spmproc_skip,
        eqlen ? (void*)strgraph : (void*)&skipdata, err);
    gt_str_reset(filename);
  }
  gt_str_delete(filename);
  return had_err;
}
