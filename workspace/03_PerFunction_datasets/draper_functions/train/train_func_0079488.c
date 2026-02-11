most_literals(Plist clauses)
{
  int max = -1;
  Plist p;
  for (p = clauses; p; p = p->next) {
    Topform c = p->v;
    int n = number_of_literals(c->literals);
    max = IMAX(max,n);
  }
  return max;
}
