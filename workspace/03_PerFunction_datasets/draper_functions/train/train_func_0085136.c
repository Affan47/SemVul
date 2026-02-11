unary_occurrences(struct syms s)
{
  int i;
  int n = 0;
  for (i = 0; i < N1; i++)
    n += s.c1[i];
  return n;
}
