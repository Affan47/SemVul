formula_to_literal(Formula f)
{
  if (f->type == NOT_FORM && f->kids[0]->type == ATOM_FORM)
    return new_literal(FALSE, copy_term(f->kids[0]->atom));
  else if (f->type == ATOM_FORM)
    return new_literal(TRUE, copy_term(f->atom));
  else
    return NULL;
}
