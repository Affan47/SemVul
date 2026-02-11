handle_literal(Term lit, Term result, Mstate state)
{
  Mclause clause_to_process = NULL;
  Mclause parent_clause = lit->container;

  int pos = lit_position(parent_clause, lit);
  BOOL negated = NEGATED(lit);
  Mstats.rewrite_bools++;


  if (negated)
    result = (result == Domain[0] ? Domain[1] : Domain[0]);
  state->stack = update_and_push((void **) &(LIT(parent_clause,pos)),
				 result, state->stack);


  if (FALSE_TERM(result)) {

    state->stack = update_and_push((void **) &(parent_clause->u.active),
				   (void *) (parent_clause->u.active-1),
				   state->stack);
    clause_to_process = parent_clause;
  }
  else

    state->stack = update_and_push((void **) &(parent_clause->subsumed),
				   (void *) TRUE, state->stack);
  return clause_to_process;
}
