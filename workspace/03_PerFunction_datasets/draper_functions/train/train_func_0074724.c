gt_bioseq_col_grep_desc(GtSeqCol *sc, char **seq,
                                   unsigned long start, unsigned long end,
                                   GtStr *seqid, GtError *err)
{
  unsigned long filenum = 0, seqnum = 0, seqlength;
  int had_err;
  GtBioseqCol *bsc;
  bsc = gt_bioseq_col_cast(sc);
  gt_error_check(err);
  gt_assert(bsc && seq && seqid);
  had_err = grep_desc(bsc, &filenum, &seqnum, seqid, err);
  if (!had_err) {
    seqlength = gt_bioseq_get_sequence_length(bsc->bioseqs[filenum], seqnum);
    if (start > seqlength - 1 || end > seqlength - 1) {
      had_err = -1;
      gt_error_set(err, "trying to extract range %lu-%lu on sequence "
                         "``%s''which is not covered by that sequence (only "
                         "%lu characters in size). Has the sequence-region "
                         "to sequence mapping been defined correctly?",
                         start, end, gt_str_get(seqid), seqlength);
    }
  }
  if (!had_err) {
    *seq = gt_bioseq_get_sequence_range(bsc->bioseqs[filenum], seqnum,
                                        start, end);
  }
  return had_err;
}
