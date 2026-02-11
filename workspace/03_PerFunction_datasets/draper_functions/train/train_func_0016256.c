para_from_alpha(struct term *alpha)
{
  struct context *into_subst, *from_subst;
  struct term *into_term;
  struct fpa_tree *ut;
  struct trail *tr;

  into_subst = get_context();
  into_subst->multiplier = 0;
  from_subst = get_context();
  from_subst->multiplier = 1;

  if (alpha->type == VARIABLE && Flags[PARA_FROM_VARS].val == 0)
    ;
  else {
    if (alpha->type == VARIABLE)
      ut = build_for_all(Fpa_clash_terms);
    else
      ut = build_tree(alpha, UNIFY, Parms[FPA_TERMS].val,
		      Fpa_clash_terms);
    into_term = next_term(ut, 0);
    while (into_term != NULL) {
      tr = NULL;
      if (unify(into_term, into_subst, alpha, from_subst, &tr)) {
	para_from_up(into_term, into_term, into_subst, alpha, from_subst);
	clear_subst_1(tr);
      }
      into_term = next_term(ut, 0);
    }
  }

  free_context(into_subst);
  free_context(from_subst);
}
