xrealloc (p, n)
     VOID *p;
     size_t n;
{
  if (p == 0)
    return xmalloc (n);
  p = realloc (p, n);
  if (p == 0)
    p = fixup_null_alloc (n);
  return p;
}
