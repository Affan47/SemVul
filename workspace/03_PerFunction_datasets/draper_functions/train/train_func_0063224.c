sbitmap_not (sbitmap dst, sbitmap src)
{
  unsigned int i, n = dst->size;
  sbitmap_ptr dstp = dst->elms;
  sbitmap_ptr srcp = src->elms;
  unsigned int last_bit;

  for (i = 0; i < n; i++)
    *dstp++ = ~*srcp++;


  last_bit = src->n_bits % SBITMAP_ELT_BITS;
  if (last_bit)
    dst->elms[n-1] = dst->elms[n-1]
      & ((SBITMAP_ELT_TYPE)-1 >> (SBITMAP_ELT_BITS - last_bit));
}
