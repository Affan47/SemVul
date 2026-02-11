rms_conflict_tautology(struct formula *f)
{
  struct formula *f1, *f2;


  if (f->type == AND_FORM) {
    for (f1 = f->first_child; f1; f1 = f1->next) {
      for (f2 = f1->next; f2; f2 = f2->next) {
	if (gen_conflict(f1, f2)) {
	  f1 = f->first_child;
	  while (f1) {
	    f2 = f1;
	    f1 = f1->next;
	    zap_formula(f2);
	  }
	  f->first_child = NULL;

	  f->type = OR_FORM;
	  return;
	}
      }
    }
  }

  else if (f->type == OR_FORM) {
    for (f1 = f->first_child; f1; f1 = f1->next) {
      for (f2 = f1->next; f2; f2 = f2->next) {
	if (gen_tautology(f1, f2)) {
	  f1 = f->first_child;
	  while (f1) {
	    f2 = f1;
	    f1 = f1->next;
	    zap_formula(f2);
	  }
	  f->first_child = NULL;

	  f->type = AND_FORM;
	  return;
	}
      }
    }
  }
}
