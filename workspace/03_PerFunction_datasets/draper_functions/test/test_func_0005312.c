gth_spliced_seq_pos_is_border(const GthSplicedSeq *spliced_seq,
                                   unsigned long position)
{
  gt_assert(spliced_seq);

  gt_assert(position < spliced_seq->splicedseqlen);
  if ((position + 1 < spliced_seq->splicedseqlen) &&
      (spliced_seq->positionmapping[position] + 1 !=
       spliced_seq->positionmapping[position+1])) {
    return true;
  }
  return false;
}
