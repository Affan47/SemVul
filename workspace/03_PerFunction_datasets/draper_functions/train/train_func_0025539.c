sbitmap_a_or_b_and_c (sbitmap dst, sbitmap a, sbitmap b, sbitmap c)
{
  unsigned int i, n = dst->size;
  sbitmap_ptr dstp = dst->elms;
  sbitmap_ptr ap = a->elms;
  sbitmap_ptr bp = b->elms;
  sbitmap_ptr cp = c->elms;

  for (i = 0; i < n; i++)
    *dstp++ = *ap++ | (*bp++ & *cp++);
}
