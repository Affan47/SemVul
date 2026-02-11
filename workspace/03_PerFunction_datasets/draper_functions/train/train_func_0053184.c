bitset_stats_xor_cmp (bitset dst, bitset src1, bitset src2)
{
  BITSET_CHECK3_ (dst, src1, src2);
  return BITSET_XOR_CMP_ (dst->s.bset, src1->s.bset, src2->s.bset);
}
