xnmalloc (size_t nmemb, size_t size)
{
  size_t n;
  void *p;

  if (xalloc_oversized (nmemb, size))
    xalloc_die ();
  n = nmemb * size;
  p = malloc (n);
  if (p == NULL)
    p = fixup_null_alloc (n);
  return p;
}
