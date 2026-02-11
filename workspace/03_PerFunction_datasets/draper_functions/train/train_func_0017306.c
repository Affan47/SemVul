distinct_vars(struct clause *c)
{
  struct literal *lit;
  int a[MAX_VARS], i, max;

  for (i = 0; i < MAX_VARS; i++)
    a[i] = -1;

  for (lit = c->first_lit, max = 0; lit; lit = lit->next_lit)
    distinct_vars_rec(lit->atom, a, &max);

  return(max);

}
