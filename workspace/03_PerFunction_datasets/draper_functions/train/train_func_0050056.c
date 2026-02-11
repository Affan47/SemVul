insert (int i, unsigned long int start, unsigned long int end, struct prof *p,
	int prof_uint)
{
  struct region *r;
  size_t to_copy;

  if (start >= end)
    return 0;

  if (prof_info.num_regions == 0)
    r = malloc (sizeof (*r));
  else
    r = realloc (prof_info.region, (prof_info.num_regions + 1) * sizeof (*r));
  if (r == NULL)
    return -1;

  to_copy = prof_info.num_regions - i;
  if (to_copy > 0)
    memmove (r + i + 1, r + i, to_copy * sizeof (*r));

  r[i].offset = p->pr_off;
  r[i].nsamples = p->pr_size / (prof_uint ? sizeof (int) : sizeof (short));
  r[i].scale = p->pr_scale;
  r[i].sample.vp = p->pr_base;
  r[i].start = start;
  r[i].end = end;

  prof_info.region = r;
  ++prof_info.num_regions;

  if (p->pr_off == 0 && p->pr_scale == 2)
    prof_info.overflow = r;

  return 0;
}
