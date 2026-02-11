formula_flatten(Formula f)
{
  int i;
  for (i = 0; i < f->arity; i++)
    f->kids[i] = formula_flatten(f->kids[i]);
  return flatten_top(f);
}
