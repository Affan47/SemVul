check_parent_pointers(Term t)
{
  if (!VARIABLE(t)) {
    int i;
    for (i = 0; i < ARITY(t); i++) {
      if (VARIABLE(ARG(t,i))) {
	if (ARG(t,i)->container != NULL) {
	  printf("check_parent_pointers, bad link: "); p_term(t);
	}
      }
      else {
	if (ARG(t,i)->container != t) {
	  printf("check_parent_pointers, bad link: "); p_term(t);
	}
      }
      set_parent_pointers(ARG(t,i));
    }
  }
}
