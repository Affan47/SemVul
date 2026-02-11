new_rat(int n, int d)
{
  CFR cf = (CFR) new_cf(sizeof(struct st_cf_rat));
  if (cf == 0) return 0;
  cf->n = n;
  cf->d = d;
  cf->next = next_rat;
  return (CF)cf;
}
