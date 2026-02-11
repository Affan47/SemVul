num_occurrences(Term t, Term a[], int n)
{
  int i, count;
  for (i = 0, count = 0; i < n; i++)
    if (term_ident(a[i], t))
      count++;
  return count;
}
