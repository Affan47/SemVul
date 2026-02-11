new_it(int (*f)(unsigned))
{
  CFI cf = (CFI) new_cf(sizeof(struct st_cf_it));
  if (cf == 0) return 0;

  cf->n = 0;
  cf->fun = f;
  cf->next = next_it;

  return (CF)cf;
}
