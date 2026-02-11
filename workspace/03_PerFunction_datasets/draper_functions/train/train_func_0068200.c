negative_clauses(Plist l)
{
  int n = 0;
  Plist p;
  for (p = l; p; p = p->next) {
    Topform c = p->v;
    if (negative_clause(c->literals))
      n++;
  }
  return n;
}
