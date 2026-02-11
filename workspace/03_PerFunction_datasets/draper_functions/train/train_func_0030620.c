closed_0(struct symbol *s)
{
  int x, c[MAX_MLITERALS];
  int n0 = s->args[0].n;


  for (x = 0; x < n0; x++)
    c[x] = ATOM1(s,x);
  add_clause(c, n0);
}
