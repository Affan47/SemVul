subst_free_var(Formula f, Term target, Term replacement)
{
  if (f->type == ATOM_FORM)
    f->atom = subst_term(f->atom, target, replacement);
  else if (quant_form(f) && str_ident(sn_to_str(SYMNUM(target)), f->qvar)) {
    ;
  }
  else {
    int i;
    for (i = 0; i < f->arity; i++)
      subst_free_var(f->kids[i], target, replacement);
  }
}
