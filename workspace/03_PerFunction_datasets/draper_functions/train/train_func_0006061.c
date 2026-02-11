seq_con_get_seq_len(void *seqs, unsigned long index)
{
  GthSeqCon *seq_con = seqs;
  gt_assert(seq_con);
  return gth_seq_con_get_length(seq_con, index);
}
