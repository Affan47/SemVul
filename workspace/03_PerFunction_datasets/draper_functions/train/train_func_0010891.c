substdio_feed(s)
register substdio *s;
{
  register int r;
  register int q;

  if (s->p) return s->p;
  q = s->n;
  r = oneread(s->op,s->fd,s->x,q);
  if (r <= 0) return r;
  s->p = r;
  q -= r;
  s->n = q;
  if (q > 0)  byte_copyr(s->x + q,r,s->x);
  return r;
}
