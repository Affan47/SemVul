gt_bioseq_get_md5_fingerprint(GtBioseq *bs, unsigned long idx)
{
  gt_assert(bs && idx < gt_bioseq_number_of_sequences(bs));
  if (!bs->md5_tab) {
    bs->md5_tab = gt_encseq_get_md5_tab(bs->encseq, NULL);
  }
  gt_assert(gt_md5_tab_get(bs->md5_tab, idx));
  return gt_md5_tab_get(bs->md5_tab, idx);
}
