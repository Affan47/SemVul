all_instances(struct term *atom)
{
  struct term *alpha, *beta, *t;
  struct term_ptr *tp, *tp1, *instances;
  struct context *subst;
  struct trail *tr;
  int i, lex_dependent, ok;

  alpha = atom->farg->argval;
  beta = atom->farg->narg->argval;
  lex_dependent = (atom->varnum == LEX_DEP_DEMOD);
  instances = NULL;
  subst = get_context();
  subst->multiplier = 1;
  for (i = 0; i <= TERM_TAB_SIZE; i++) {
    tp = (i == TERM_TAB_SIZE ? Bd_kludge : Term_tab[i]);
    while (tp != NULL) {
      tr = NULL;
      if (match(alpha, subst, tp->term, &tr)) {

	if (lex_dependent == 0)
	  ok = 1;
	else {
	  t = apply(beta, subst);
	  if (Flags[LRPO].val)
	    ok = lrpo_greater(tp->term, t);
	  else
	    ok = (lex_check(t, tp->term) == LESS_THAN);
	  zap_term(t);
	}

	if (ok) {
	  tp1 = get_term_ptr();
	  tp1->term = tp->term;
	  tp1->next = instances;
	  instances = tp1;
	}

	clear_subst_1(tr);
      }
      tp = tp->next;
    }
  }
  free_context(subst);
  return(instances);
}
