gt_reads2twobit_write_encseq_varlen(GtReads2Twobit *r2t,
    GtError *err)
{
  int had_err = 0;
  GtFilelengthvalues *filelengthtab;
  GtStrArray *filenametab;
  uint64_t sizeofrep, minsizeofrep;
  unsigned long numofdbfiles = gt_array_size(r2t->collection);
  GtEncseqAccessType sat;
  unsigned long idx, lengthofdbfilenames = 0;

  gt_assert(r2t->seppos != NULL);
  gt_reads2twobit_collect_fileinfo(r2t, &filelengthtab, &filenametab);
  for (idx = 0; idx < gt_str_array_size(filenametab); idx++)
  {
    lengthofdbfilenames += gt_str_length(gt_str_array_get_str(
          filenametab, idx)) + 1UL;
  }
  sat = GT_ACCESS_TYPE_UCHARTABLES;
  minsizeofrep = GT_READS2TWOBIT_SIZEOFREP(sat);
  sizeofrep = GT_READS2TWOBIT_SIZEOFREP(GT_ACCESS_TYPE_USHORTTABLES);
  if (sizeofrep < minsizeofrep)
  {
    sat = GT_ACCESS_TYPE_USHORTTABLES;
    minsizeofrep = sizeofrep;
  }
  sizeofrep = GT_READS2TWOBIT_SIZEOFREP(GT_ACCESS_TYPE_UINT32TABLES);
  if (sizeofrep < minsizeofrep)
    sat = GT_ACCESS_TYPE_UINT32TABLES;
  gt_reads2twobit_set_separators_to_less_frequent_char(r2t);
  gt_reads2twobit_zeropad_tbe(r2t);
  had_err = gt_encseq_seppos2ssptab(gt_str_get(r2t->indexname),
      r2t->total_seqlength, r2t->nofseqs, r2t->seppos, err);
  if (!had_err)
    had_err = gt_encseq_generic_write_twobitencoding_to_file(
        gt_str_get(r2t->indexname), r2t->total_seqlength,
        sat, 0, r2t->seqlen_min - 1UL, r2t->seqlen_max - 1UL, 0, 0,
        r2t->seqlen_max - 1UL, r2t->twobitencoding, r2t->nofseqs,
        numofdbfiles, filelengthtab, filenametab, r2t->chardistri, err);
  gt_free(filelengthtab);
  gt_str_array_delete(filenametab);
  return had_err;
}
