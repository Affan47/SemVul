weight(Term t, Context subst)
{
  if (VARIABLE(t))
    return Variable_weight;
  else {

    Plist p;
    for (p = Rules; p; p = p->next) {
      Term rule = p->v;
      Term alpha = ARG(rule,0);
      Term beta  = ARG(rule,1);
      Trail tr = NULL;
      if (match_weight(ARG(alpha,0), subst, t, &tr, Avar_sn)) {

	double wt = weight_calc(beta, subst);
	undo_subst(tr);
	return wt;
      }
    }

    if (CONSTANT(t)) {
      if (skolem_term(t) && Sk_constant_weight != 1)
	return Sk_constant_weight;
      else if (relation_symbol(SYMNUM(t)))
	return Prop_atom_weight;
      else
	return Constant_weight;
    }
    else {

      double wt = 1;
      int i;
      for (i = 0; i < ARITY(t); i++) {
	double arg_wt = weight(ARG(t, i), subst);

	if (Nest_penalty != 0 &&
	    ARITY(t) <= 2 &&
	    SYMNUM(t) == SYMNUM(ARG(t,i)))
	  wt += Nest_penalty;

	wt += arg_wt;
      }
      return wt;
    }
  }
}
