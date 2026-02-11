inside_polygon (trap_t *t, segment_t* seg)
{
  int rseg = t->rseg;

  if (t->state == ST_INVALID)
    return 0;

  if ((t->lseg <= 0) || (t->rseg <= 0))
    return 0;

  if (((t->u0 <= 0) && (t->u1 <= 0)) ||
      ((t->d0 <= 0) && (t->d1 <= 0)))
    return (_greater_than(&seg[rseg].v1, &seg[rseg].v0));

  return 0;
}
