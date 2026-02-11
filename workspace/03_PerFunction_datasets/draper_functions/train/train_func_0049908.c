hint2_subsumed(struct clause *c)
{
  struct literal *lit = first_nonanswer_lit(c);
  if (lit != NULL) {
    struct fpa_tree *ut = build_tree(lit->atom,
				     MORE_GEN,
				     Parms[FPA_LITERALS].val,
				     Fpa_hints2_lits);
    struct term *fatom = next_term(ut, 0);
    while (fatom != NULL) {
      struct literal *flit = fatom->occ.lit;
      if (lit->sign == flit->sign) {
	struct clause *hint = flit->container;
	if (subsume(hint, c)) {
	  zap_prop_tree(ut);
	  return hint;
	}
      }
      fatom = next_term(ut, 0);
    }
  }
  return NULL;
}
