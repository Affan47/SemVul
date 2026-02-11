initialise(n)
     int n;
{
    int i;

  for (i = 1; i <= n; i++)
    seg[i].is_inserted = FALSE;

  generate_random_ordering(n);

  return 0;
}
