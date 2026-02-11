onto(struct symbol *s)
{
  int x, y, c[MAX_MLITERALS];
  int n0 = s->args[0].n;
  int n1 = s->args[1].n;


  for (x = 0; x < n1; x++) {
    for (y = 0; y < n0; y++)
      c[y] = ATOM2(s,y,x);
    add_clause(c, n1);
  }
}
