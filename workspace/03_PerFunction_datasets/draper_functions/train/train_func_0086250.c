gt_bioseq_get_encoded_char(const GtBioseq *bs, unsigned long index,
                                   unsigned long position)
{
  unsigned long startpos;
  gt_assert(bs);
  gt_assert(index < gt_encseq_num_of_sequences(bs->encseq));
  startpos = gt_encseq_seqstartpos(bs->encseq, index);
  return gt_encseq_get_encoded_char(bs->encseq, startpos + position,
                                    GT_READMODE_FORWARD);
}
