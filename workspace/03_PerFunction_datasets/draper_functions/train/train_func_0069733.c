subst_atomic_formula(Formula f, Formula target, Formula replacement)
{


  if (f->type == ATOM_FORM) {
    if (SYMNUM(f->atom) == SYMNUM(target->atom)) {
      Formula new = formula_copy(replacement);
      Plist vars  = plist_of_subterms(target->atom);
      Plist terms = plist_of_subterms(f->atom);


      Ilist constants_in_f = constants_in_formula(f);
      rename_these_bound_vars(new, constants_in_f);
      subst_free_vars(new, vars, terms, NULL);
      zap_plist(vars);
      zap_plist(terms);
      zap_ilist(constants_in_f);
      zap_term(f->atom);
      return new;
    }
  }
  else {
    int i;
    for (i = 0; i < f->arity; i++)
      f->kids[i] = subst_atomic_formula(f->kids[i], target, replacement);
  }
  return f;
}
