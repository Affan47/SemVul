term_to_formula(Term t)
{
  Formula f = NULL;
  Ftype type;
  Attribute attributes = NULL;

  if (is_term(t, attrib_sym(), 2)) {
    attributes = term_to_attributes(ARG(t,1), attrib_sym());
    t = ARG(t,0);
  }

  if (is_term(t, quant_sym(), 3)) {

    Term quant = ARG(t,0);
    Term var = ARG(t,1);
    Ftype qtype = (is_term(quant, all_sym(), 0) ? ALL_FORM : EXISTS_FORM);
    f = formula_get(1, qtype);
    f->kids[0] = term_to_formula(ARG(t,2));
    f->qvar = sn_to_str(SYMNUM(var));
  }
  else {
    if (is_term(t, true_sym(), 0))
      type = AND_FORM;
    else if (is_term(t, false_sym(), 0))
      type = OR_FORM;
    else if (is_term(t, not_sym(), 1))
      type = NOT_FORM;
    else if (is_term(t, and_sym(), 2))
      type = AND_FORM;
    else if (is_term(t, or_sym(), 2))
      type = OR_FORM;
    else if (is_term(t, iff_sym(), 2))
      type = IFF_FORM;
    else if (is_term(t, imp_sym(), 2))
      type = IMP_FORM;
    else if (is_term(t, impby_sym(), 2))
      type = IMPBY_FORM;
    else
      type = ATOM_FORM;

    if (type == ATOM_FORM) {
      f = formula_get(0, ATOM_FORM);
      f->atom = copy_term(t);
    }
    else if (type == NOT_FORM) {
      f = formula_get(1, NOT_FORM);
      f->kids[0] = term_to_formula(ARG(t,0));
    }
    else if (ARITY(t) == 0) {
      f = formula_get(0, type);
    }
    else {
      f = formula_get(2, type);
      f->kids[0] = term_to_formula(ARG(t,0));
      f->kids[1] = term_to_formula(ARG(t,1));
    }
  }
  f = flatten_top(f);
  f->attributes = attributes;
  return f;
}
