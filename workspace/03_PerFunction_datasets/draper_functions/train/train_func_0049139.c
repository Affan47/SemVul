dual(Formula f)
{
  int i;
  for (i = 0; i < f->arity; i++)
    f->kids[i] = dual(f->kids[i]);

  f->type = dual_type(f->type);
  return f;
}
