abitset_copy1 (bitset dst, bitset src)
{
  bitset_word *srcp = ABITSET_WORDS (src);
  bitset_word *dstp = ABITSET_WORDS (dst);
  bitset_windex size = dst->b.csize;

  if (srcp == dstp)
      return;
  memcpy (dstp, srcp, sizeof (bitset_word) * size);
}
