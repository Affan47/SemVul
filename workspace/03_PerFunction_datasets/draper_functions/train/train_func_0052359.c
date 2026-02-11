cnf(struct formula *f)
{
  struct formula *f1, *f2, *f_prev, *f_next, *f_save;

  f_save = f->next; f->next = NULL;

  if (f->type == AND_FORM || f->type == OR_FORM) {

    f_prev = NULL;
    f1 = f->first_child;
    while(f1) {
      f_next = f1->next;
      f2 = cnf(f1);
      if (f_prev)
	f_prev->next = f2;
      else
	f->first_child = f2;
      f_prev = f2;
      f1 = f_next;
    }

    if (f->type == AND_FORM) {
      flatten_top(f);
      if (Flags[SIMPLIFY_FOL].val) {
	conflict_tautology(f);
	f = subsume_conj(f);
      }
    }
    else
      f = distribute(f);
  }

  f->next = f_save;
  return(f);

}
