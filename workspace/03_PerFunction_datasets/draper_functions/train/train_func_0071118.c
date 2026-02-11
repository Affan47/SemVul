state_reduction_find (state *s, rule *r)
{
  int i;
  reductions *reds = s->reductions;
  for (i = 0; i < reds->num; ++i)
    if (reds->rules[i] == r)
      return i;
  return -1;
}
