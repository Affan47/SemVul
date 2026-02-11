gt_bioseq_get_sequence(const GtBioseq *bs, unsigned long idx)
{
  char *out;
  unsigned long startpos;
  gt_assert(bs);
  gt_assert(idx < gt_encseq_num_of_sequences(bs->encseq));
  out = gt_calloc(gt_encseq_seqlength(bs->encseq, idx), sizeof (char));
  startpos = gt_encseq_seqstartpos(bs->encseq, idx);
  gt_encseq_extract_decoded(bs->encseq, out, startpos,
                            startpos
                              + gt_encseq_seqlength(bs->encseq, idx) - 1);
  return out;
}
