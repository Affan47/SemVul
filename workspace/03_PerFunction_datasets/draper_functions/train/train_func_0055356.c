gt_seq_get_encoded(GtSeq *s)
{
  gt_assert(s);
  if (!s->encoded_seq) {
    s->encoded_seq = gt_malloc(sizeof (char) * (s->seqlen+1));
    gt_alphabet_encode_seq(s->seqalpha, s->encoded_seq, (char*) s->seq,
                           s->seqlen);
    s->encoded_seq[s->seqlen] = '\0';
  }
  return s->encoded_seq;
}
