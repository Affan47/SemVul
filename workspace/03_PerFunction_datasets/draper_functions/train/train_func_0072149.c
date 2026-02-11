para_pos(Topform from_clause, Ilist from_pos,
		 Topform into_clause, Ilist into_pos)
{
  Context cf = get_context();
  Context ci = get_context();
  Trail tr = NULL;
  Topform paramodulant;
  BOOL ok;

  Literals from_lit = ith_literal(from_clause->literals, from_pos->i);
  Literals into_lit = ith_literal(into_clause->literals, into_pos->i);
  int from_side = (from_pos->next->i == 1 ? 0 : 1);
  Term alpha = ARG(from_lit->atom, from_side);
  Term into_term = term_at_pos(into_lit->atom, into_pos->next);
  if (into_term == NULL)
    fatal_error("paramod2_instances, term does not exist");

  ok = unify(alpha, cf, into_term, ci, &tr);
  if (!ok)
    fatal_error("para_pos, terms do not unify");

  paramodulant = paramodulate(from_lit, from_side, cf,
			      into_clause, into_pos, ci);

  paramodulant->justification = para_just(PARA_JUST,
					  from_clause, copy_ilist(from_pos),
					  into_clause, copy_ilist(into_pos));
  renumber_variables(paramodulant, MAX_VARS);
  undo_subst(tr);
  free_context(cf);
  free_context(ci);
  return paramodulant;
}
