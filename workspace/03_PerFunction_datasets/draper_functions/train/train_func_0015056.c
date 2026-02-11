gt_bioseq_col_md5_to_seq(GtSeqCol *sc, char **seq,
                                    unsigned long start, unsigned long end,
                                    GtStr *md5_seqid, GtError *err)
{
  unsigned long i, seqnum = GT_UNDEF_ULONG;
  char *seqid = NULL;
  int had_err = 0;
  GtBioseq *bioseq = NULL;
  GtBioseqCol *bsc;
  bsc = gt_bioseq_col_cast(sc);
  gt_error_check(err);
  gt_assert(bsc && seq && md5_seqid && err);
  gt_assert(gt_md5_seqid_has_prefix(gt_str_get(md5_seqid)));

  if (gt_str_length(md5_seqid) >= GT_MD5_SEQID_TOTAL_LEN) {
    seqid = gt_str_get(md5_seqid);
    if (seqid[GT_MD5_SEQID_TOTAL_LEN-1] != GT_MD5_SEQID_SEPARATOR) {
      gt_error_set(err, "MD5 sequence id %s not terminated with '%c'",
                   gt_str_get(md5_seqid), GT_MD5_SEQID_SEPARATOR);
      had_err = -1;
    }
    if (!had_err)
      seqid[GT_MD5_SEQID_TOTAL_LEN-1] = '\0';
  }
  for (i = 0; !had_err && i < bsc->num_of_seqfiles; i++) {
    bioseq = bsc->bioseqs[i];
    seqnum = gt_bioseq_md5_to_index(bioseq, gt_str_get(md5_seqid) +
                                    GT_MD5_SEQID_PREFIX_LEN);
    if (seqnum != GT_UNDEF_ULONG)
      break;
  }
  if (!had_err) {
    if (gt_str_length(md5_seqid) >= GT_MD5_SEQID_TOTAL_LEN)
      seqid[GT_MD5_SEQID_TOTAL_LEN-1] = GT_MD5_SEQID_SEPARATOR;
    if (seqnum != GT_UNDEF_ULONG) {
      *seq = gt_bioseq_get_sequence_range(bioseq, seqnum, start, end);
    }
    else {
      gt_error_set(err, "sequence %s not found", gt_str_get(md5_seqid));
      had_err = -1;
    }
  }
  return had_err;
}
