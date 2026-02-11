formula_copy(Formula f)
{
  Formula g = formula_get(f->arity, f->type);

  if (f->type == ATOM_FORM)
    g->atom = copy_term(f->atom);
  else {
    int i;
    if (quant_form(f))
      g->qvar = f->qvar;
    for (i = 0; i < f->arity; i++)
      g->kids[i] = formula_copy(f->kids[i]);
  }
  return g;
}
