ts_and_fs(struct formula *f)
{
  struct formula *f1, *f2, *f_prev;
  int f_type;

  f_type = f->type;
  if (f_type != AND_FORM && f_type != OR_FORM)
    return;
  else {
    f_prev = NULL;
    f1 = f->first_child;
    while (f1 != NULL) {
      if ((f1->type == AND_FORM || f1->type == OR_FORM) &&
	  f1->first_child == NULL) {
	if (f_type != f1->type) {
	  f->type = f1->type;
	  f1 = f->first_child;
	  while (f1) {
	    f2 = f1;
	    f1 = f1->next;
	    zap_formula(f2);
	  }
	  f->first_child = NULL;

	  f->type = (f->type == AND_FORM ? OR_FORM : AND_FORM);
	  return;
	}
	else {
	  if (f_prev == NULL)
	    f->first_child = f1->next;
	  else
	    f_prev->next = f1->next;

	  f2 = f1;
	  f1 = f1->next;
	  free_formula(f2);
	}
      }
      else {
	f_prev = f1;
	f1 = f1->next;
      }
    }
  }
}
