gt_seq_col_grep_desc_md5(GtSeqCol *sc, const char **md5, GtStr *seqid,
                             GtError *err)
{
  gt_assert(sc && md5 && seqid);
  if (sc->c_class->grep_desc_md5)
    return sc->c_class->grep_desc_md5(sc, md5, seqid, err);
  return 0;
}
