formula_size(Formula f)
{
  if (f->type == ATOM_FORM)
    return 1;
  else {
    int i;
    int n = 0;
    for (i = 0; i < f->arity; i++)
      n += formula_size(f->kids[i]);
    return n+1;
  }
}
