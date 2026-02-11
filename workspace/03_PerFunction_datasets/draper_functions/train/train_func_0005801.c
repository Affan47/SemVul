zap_formula(struct formula *f)
{
  struct formula *f1, *f2;

  if (f->type == ATOM_FORM)
    zap_term(f->t);
  else {
    f1 = f->first_child;
    while (f1) {
      f2 = f1;
      f1 = f1->next;
      zap_formula(f2);
    }
    if (f->type == QUANT_FORM)
      zap_term(f->t);
  }
  free_formula(f);
}
