miniscope(Formula f)
{
  if (f->type == ATOM_FORM || f->type == NOT_FORM)
    return f;
  if (f->type == AND_FORM) {
    int i;
    for (i = 0; i < f->arity; i++)
      f->kids[i] = miniscope(f->kids[i]);
    f = flatten_top(f);
    f = simplify_and_share(f);
    return f;
  }
  else if (f->type == OR_FORM) {
    int i;
    for (i = 0; i < f->arity; i++)
      f->kids[i] = miniscope(f->kids[i]);
    f = flatten_top(f);
    f = dual(remove_subsumed_share(dual(f)));
    f = balanced_binary(f);
    f = distribute(f);
    return f;
  }
  else if (f->type == EXISTS_FORM) {
    f = dual(f);
    f = miniscope(f);
    f = dual(f);
    return f;
  }
  else if (f->type == ALL_FORM) {

    f->kids[0] = miniscope(f->kids[0]);

    if (f->kids[0]->type == AND_FORM) {

      int i;
      Formula and = f->kids[0];
      free_formula(f);
      for (i = 0; i < and->arity; i++) {
	Formula g = get_quant_form(ALL_FORM, f->qvar, and->kids[i]);
	g = ms_free_vars(g);
	and->kids[i] = g;
      }
      return and;
    }
    else {
      f = ms_free_vars(f);
      return f;
    }
  }
  else {
    fatal_error("miniscope: formula not in nnf");
    return NULL;
  }
}
