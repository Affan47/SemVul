lookup(const char *n, bool create)
{
  if (nbuckets <= 0)
    resize(7);
  unsigned int h = hashcode(n);
  int i = h % nbuckets;
  struct sym *r = buckets[i];
  while (r && strcmp(n,r->n))
    r = r->l;
  if (!r && create)
    {
      nelems += 1;
      r = new sym;
      r->h = h;
      r->l = buckets[i];
      r->n = new char [1+strlen(n)];
      strcpy(r->n, n);
      buckets[i] = r;
      if ( 2 * nelems > 3 * nbuckets)
        resize(2*nbuckets-1);
    }
  return r;
}
