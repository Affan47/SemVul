jrb_find_gen(JRB n, Jval key, int (*fxn)(Jval, Jval))
{
  int fnd;
  JRB j;

  j = jrb_find_gte_gen(n, key, fxn, &fnd);
  if (fnd) return j; else return NULL;
}
