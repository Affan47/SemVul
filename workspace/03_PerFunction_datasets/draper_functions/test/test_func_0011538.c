gt_golomb_bitwise_decoder_new(GtGolomb *golomb)
{
  GtGolombBitwiseDecoder *gbwd;
  gt_assert(golomb);
  gbwd = gt_malloc(sizeof (*gbwd));
  gbwd->median = golomb->median;
  gbwd->status = IN_Q;
  gbwd->cur_r_bit = 0;
  gbwd->quotient = 0;
  gbwd->remain = 0;
  gbwd->len = golomb->len;
  gbwd->two_pow_len = golomb->two_pow_len;
  return gbwd;
}
