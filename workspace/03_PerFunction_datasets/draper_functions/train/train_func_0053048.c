foffer_clausify(Formula f)
{
  Plist clauses = clausify_formula(f);
  Plist p;
  for (p = clauses; p; p = p->next) {
    Topform c = p->v;
    c->justification = input_just();
  }
  return clauses;
}
