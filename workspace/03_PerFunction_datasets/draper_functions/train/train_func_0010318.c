track_cmp_wrapper(const void *t1, const void *t2, void *data)
{
  const char *s1 = (const char*) t1, *s2 = (const char*) t2;
  GtLayoutTraverseInfo *lti = (GtLayoutTraverseInfo*) data;
  gt_assert(t1 && t2 && lti && lti->layout);
  return lti->layout->track_ordering_func(s1, s2, lti->layout->t_cmp_data);
}
