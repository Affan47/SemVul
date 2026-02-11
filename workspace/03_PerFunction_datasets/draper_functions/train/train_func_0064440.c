insert (position p, position_set * s)
{
  size_t count = s->nelem;
  size_t lo = 0, hi = count;
  size_t i;
  while (lo < hi)
    {
      size_t mid = (lo + hi) >> 1;
      if (s->elems[mid].index > p.index)
        lo = mid + 1;
      else
        hi = mid;
    }

  if (lo < count && p.index == s->elems[lo].index)
    {
      s->elems[lo].constraint |= p.constraint;
      return;
    }

  REALLOC_IF_NECESSARY (s->elems, s->alloc, count + 1);
  for (i = count; i > lo; i--)
    s->elems[i] = s->elems[i - 1];
  s->elems[lo] = p;
  ++s->nelem;
}
