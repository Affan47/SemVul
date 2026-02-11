xx_resolve2(Topform c, int n, BOOL renumber_vars)
{
  Topform res;
  Literals l = ith_literal(c->literals, n);
  Context s = get_context();
  Trail tr = NULL;

  if (neg_eq(l) &&
      unify(ARG(l->atom,0), s,
	    ARG(l->atom,1), s, &tr)) {
    Literals lit;
    res = get_topform();
    for (lit = c->literals; lit; lit = lit->next)
      if (lit != l)
	res->literals = append_literal(res->literals, apply_lit(lit,  s));

    res->attributes = inheritable_att_instances(c->attributes, s);
    res->justification = xxres_just(c, n);
    upward_clause_links(res);
    if (renumber_vars)
      renumber_variables(res, MAX_VARS);
    undo_subst(tr);
  }
  else
    res = NULL;
  free_context(s);
  return res;
}
