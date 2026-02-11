all_clauses_unit(Plist l)
{
  Plist p;
  for (p = l; p; p = p->next) {
    Topform c = p->v;
    if (!unit_clause(c->literals))
      return FALSE;
  }
  return TRUE;
}
