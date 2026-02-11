kdt_create (Kdt * kdt, const char * name, int blksize,
		KdtPoint * a, long len)
{
  int npmax = blksize/sizeof (KdtPoint);
  if (kdt_init (kdt, name, npmax, len))
    return -1;

  long i;
  for (i = 0; i < len; i++) {
    if (a[i].x > kdt->h.bound[0].h) kdt->h.bound[0].h = a[i].x;
    if (a[i].x < kdt->h.bound[0].l) kdt->h.bound[0].l = a[i].x;
    if (a[i].y > kdt->h.bound[1].h) kdt->h.bound[1].h = a[i].y;
    if (a[i].y < kdt->h.bound[1].l) kdt->h.bound[1].l = a[i].y;
  }

  fwrite (&kdt->h, sizeof (Header), 1, kdt->nodes);
  split (a, kdt->h.bound, kdt->h.len, 0, kdt);

  return 0;
}
