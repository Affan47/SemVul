sbitmap_not (dst, src)
     sbitmap dst, src;
{
  unsigned int i, n = dst->size;
  sbitmap_ptr dstp = dst->elms;
  sbitmap_ptr srcp = src->elms;

  for (i = 0; i < n; i++)
    *dstp++ = ~*srcp++;
}
