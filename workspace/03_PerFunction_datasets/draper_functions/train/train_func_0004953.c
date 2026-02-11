xrealloc (void *p, size_t n)
{
  p = realloc (p, n);
  if (!p && n != 0)
    xalloc_die ();
  return p;
}
